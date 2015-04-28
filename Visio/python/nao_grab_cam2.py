import numpy as np
import Image, cv2
import sys, time, math
from naoqi import ALProxy

pi = 3.14

#** NAO keeps watching JOGs and protects himself from them
#*
#*  by Cyril Rouviere

# NAO parameters
IP, PORT = "127.0.0.1", 9559
ALMEMORY_KEY_NAMES = ["Device/SubDeviceList/HeadYaw/Position/Sensor/Value", "Device/SubDeviceList/HeadPitch/Position/Sensor/Value"]
ALMEMORY_KEY_ARMS = [
	"Device/SubDeviceList/LShoulderPitch/Position/Sensor/Value",
	"Device/SubDeviceList/LShoulderRoll/Position/Sensor/Value",
	"Device/SubDeviceList/LElbowYaw/Position/Sensor/Value",
	"Device/SubDeviceList/LWristYaw/Position/Sensor/Value",
	"Device/SubDeviceList/LHand/Position/Sensor/Value",
	"Device/SubDeviceList/RShoulderPitch/Position/Sensor/Value",
	"Device/SubDeviceList/RShoulderRoll/Position/Sensor/Value",
	"Device/SubDeviceList/RElbowYaw/Position/Sensor/Value",
	"Device/SubDeviceList/RWristYaw/Position/Sensor/Value",
	"Device/SubDeviceList/RHand/Position/Sensor/Value"]

angles_punch = [
	[0., -0.3, -pi/2, -pi/2, -pi/2, 0.,		0., +0.3, pi/2, pi/2, pi/2, 0.],
	[0., 0., 0., 0., 0., 0.,				0., +0.3, pi/2, pi/2, pi/2, 0.]
]
commandes_punch = [
	"LShoulderPitch",
	"LShoulderRoll",
	"LElbowYaw",
	"LElbowRoll",
	"LWristYaw",
	"LHand",
	"RShoulderPitch",
	"RShoulderRoll",
	"RElbowYaw",
	"RElbowRoll",
	"RWristYaw",
	"RHand"	
]

# Detection threshold and counter parameters
temps = 200000
seuil_mid = 300
seuil_ecart = 100
seuil_min = 4
seuil_punch = 400
state_punch = 0
HSV_min = np.array((2, 150, 120))
HSV_max = np.array((14, 255, 255))

# Movement parameters
Kp_head_x = -0.3
Kp_head_y = +0.3
Kp_walk_theta = +0.5
Kp_walk_vitesse = 0.01

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

def armData():
	memory = ALProxy("ALMemory", IP, PORT)
	data = list()
	for key in ALMEMORY_KEY_ARMS:
		value = memory.getData(key)
		data.append(value)
	return data

def punch(prox, n):
	prox.setAngles(commandes_punch, angles_punch[n], 0.3)

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
motionProxy.setWalkArmsEnabled(False, False)
motionProxy.setMotionConfig([["ENABLE_FOOT_CONTACT_PROTECTION", True]])

# Camera
camProxy = ALProxy("ALVideoDevice", IP, PORT)
camProxy.setParam(18, 0)	# "kCameraSelectID", 0 : camera top, 1 : camera bottom
resolution = 0				# 0 : QQVGA, 1 : QVGA, 2 : VGA
colorSpace = 11				# RGB
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
	x_head, y_head = recordData()
	theta_body = x_head
	v_theta_body = 0.0
	vitesse = 0.0

	for c in contours:
		area = cv2.contourArea(c)
		if area > best_area: best_area, best_c = area, c

	if best_area > 0:

		# Centroid of The Chosen One
		M = cv2.moments(best_c)
		cx, cy = int(M['m10'] / M['m00']), int(M['m01'] / M['m00'])
		cv2.circle(img_brute, (cx, cy), 5, 255, -1)
		dx_img = (float(cx) - middle_x) / imageWidth
		dy_img = (float(cy) - middle_y) / imageHeight

		# NAO jobs
		x_head += Kp_head_x * dx_img
		y_head += Kp_head_y * dy_img
		print "aire : ", best_area, " | dx : ", dx_img, " | dy : ", dy_img
		if abs(theta_body) > 0.5:
			v_theta_body = Kp_walk_theta * theta_body
		if best_area > seuil_min and abs(best_area - seuil_min) > seuil_ecart:
			vitesse = (seuil_mid - best_area) * Kp_walk_vitesse
		if v_theta_body < -0.9 : v_theta_body = -0.9
		if v_theta_body > +0.9 : v_theta_body = +0.9
		if abs(v_theta_body) < 0.2 : v_theta_body = 0.0
		if vitesse > +0.9 : vitesse = +0.9
		if vitesse < -0.9 : vitesse = -0.9
		if abs(vitesse) < 0.2 : vitesse = 0.0

	if state_punch > 0:
		state_punch += 1
		if state_punch == 10:
			state_punch = 0
	elif best_area > seuil_punch:
		punch(motionProxy, 1)
		vitesse = 0.
		v_theta_body = 0.
	else:
		punch(motionProxy, 0)


	motionProxy.setWalkTargetVelocity(vitesse, 0.0, v_theta_body, 0.8)
	motionProxy.setAngles("HeadYaw", x_head, 0.3)
	motionProxy.setAngles("HeadPitch", y_head, 0.3)


	if best_area == 0: setLeds(0, 255, 0)
	else: setLeds(255, 0, 0)


camProxy.unsubscribe(videoClient)
postureProxy.goToPosture("Sit", 0.8)
StiffnessOn(motionProxy, False)
