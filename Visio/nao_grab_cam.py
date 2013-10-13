import numpy as np
import Image, cv2
import sys, time, math
from naoqi import ALProxy

#** NAO keeps watching JOGs and protects himself from them
#*
#*  by Cyril Rouviere

# NAO parameters
IP, PORT = "127.0.0.1", 9559
ALMEMORY_KEY_NAMES = ["Device/SubDeviceList/HeadYaw/Position/Sensor/Value", "Device/SubDeviceList/HeadPitch/Position/Sensor/Value"]

# Detection threshold and counter parameters
temps = 200000
seuil_max = 150	# area > seuil => unwalk
seuil_mid = 100	# area > seuil => stay
seuil_min = 4	# area > seuil => walk
HSV_min = np.array((2, 150, 120))
HSV_max = np.array((14, 255, 255))

# Movement parameters
bangbang = 0.9
inv_coeff_x, inv_coeff_y = -3.0, 3.0

def StiffnessOn(proxy, ok):
	pNames = "Body"
	pStiffnessLists = 1.0 if ok else 0.0
	pTimeLists = 1.0
	proxy.stiffnessInterpolation(pNames, pStiffnessLists, pTimeLists)

def recordData():
	memory = ALProxy("ALMemory", IP, PORT)
	data = list()
	for key in ALMEMORY_KEY_NAMES:
		value = memory.getData(key)
		data.append(value)
	return data

# LEDs parameters
def setLeds(R, G, B):
	ledsProxy = ALProxy("ALLeds", IP, PORT)
	ledsProxy.setIntensity('AllLedsRed', float(R) / 255.0)
	ledsProxy.setIntensity('AllLedsGreen', float(G) / 255.0)
	ledsProxy.setIntensity('AllLedsBlue', float(B) / 255.0)

# Motion
motionProxy = ALProxy("ALMotion", IP, PORT)
postureProxy = ALProxy("ALRobotPosture", IP, PORT)
StiffnessOn(motionProxy, True)
postureProxy.goToPosture("StandInit", 1.0)
motionProxy.moveInit()
motionProxy.setWalkArmsEnabled(True, True)
motionProxy.setMotionConfig([["ENABLE_FOOT_CONTACT_PROTECTION", True]])

# Camera
camProxy = ALProxy("ALVideoDevice", IP, PORT)
camProxy.setParam(18, 0)	# "kCameraSelectID", 0 : camera top, 1 : camera bottom
resolution = 0			# 0 : QQVGA, 1 : QVGA, 2 : VGA
colorSpace = 11			# RGB
videoClient = camProxy.subscribe("python_client", resolution, colorSpace, 5)
from_video = camProxy.getImageRemote(videoClient)
imageWidth, imageHeight = from_video[0], from_video[1]
middle_x, middle_y = float(imageWidth / 2), float(imageHeight / 2)

# Speaker
c3po = ALProxy("ALTextToSpeech", IP, PORT)

for i in range(0, temps):

	# Grab the image (it is not a BGR, but a RGB)
	from_video = camProxy.getImageRemote(videoClient)
	img_nao = from_video[6]
	img_PIL = Image.fromstring("RGB", (imageWidth, imageHeight), img_nao)
	img_brute = cv2.cvtColor(np.asarray(img_PIL), cv2.COLOR_RGB2BGR)

	# Smooth, convert to HSV, filter and contours
	img_smoothed = cv2.blur(img_brute,(3,3))
	img_HSV = cv2.cvtColor(img_smoothed, cv2.COLOR_BGR2HSV)
	img_filtree = cv2.inRange(img_HSV, HSV_min, HSV_max)
	contours, hierarchy = cv2.findContours(img_filtree, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

	# The Chosen One
	best_area = 0
	theta = 0.0
	vitesse = 0.0
	for c in contours:
		area = cv2.contourArea(c)
		if area > best_area: best_area, best_c = area, c

	if best_area > 0:

		# Centroid of The Chosen One
		M = cv2.moments(best_c)
		cx, cy = int(M['m10'] / M['m00']), int(M['m01'] / M['m00'])
		cv2.circle(img_brute, (cx, cy), 5, 255, -1)
		dx = (float(cx) - middle_x) / (imageWidth * inv_coeff_x)
		dy = (float(cy) - middle_y) / (imageHeight * inv_coeff_y)

		# NAO jobs
		x, y = recordData()
		x, y = x + dx, y + dy
		theta = x
		print "aire : ", best_area, " | dx : ", dx, " | dy : ", dy
		motionProxy.setAngles("HeadYaw", x, 0.3)
		motionProxy.setAngles("HeadPitch", y, 0.3)

	if theta < -0.9 : theta = -0.9
	if theta > +0.9 : theta = +0.9
	if best_area > seuil_max:
		vitesse = -bangbang
	elif best_area < seuil_mid and best_area > seuil_min:
		vitesse = +bangbang
	else:
		vitesse = 0.0
		if theta > -0.3 and theta < +0.3: theta = 0.0
	motionProxy.setWalkTargetVelocity(vitesse, 0.0, theta, 0.8)

	if best_area == 0: setLeds(0, 255, 0)
	else: setLeds(255, 0, 0)

	time.sleep(0.1)

camProxy.unsubscribe(videoClient)
postureProxy.goToPosture("Sit", 0.8)
StiffnessOn(motionProxy, False)
