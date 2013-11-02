import numpy as np
import Image, cv2
import sys, time
from naoqi import ALProxy

#** Grab images from NAO camera : img_brute
#*
#*  by Cyril Rouviere

# NAO parameters
IP, PORT = "127.0.0.1", 9559
temps = 200000

# Camera
camProxy = ALProxy("ALVideoDevice", IP, PORT)
camProxy.setParam(18, 0)	# "kCameraSelectID", 0 : camera top, 1 : camera bottom
resolution = 0			# 0 : QQVGA, 1 : QVGA, 2 : VGA
colorSpace = 11			# RGB
videoClient = camProxy.subscribe("python_client", resolution, colorSpace, 5)
from_video = camProxy.getImageRemote(videoClient)
imageWidth, imageHeight = from_video[0], from_video[1]

for i in range(0, temps):

	# Grab the image (it is not a BGR, but a RGB)
	from_video = camProxy.getImageRemote(videoClient)
	img_nao = from_video[6]
	img_PIL = Image.fromstring("RGB", (imageWidth, imageHeight), img_nao)
	img_brute = cv2.cvtColor(np.asarray(img_PIL), cv2.COLOR_RGB2BGR)

	time.sleep(0.1)

camProxy.unsubscribe(videoClient)
