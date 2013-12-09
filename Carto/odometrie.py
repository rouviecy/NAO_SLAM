import math, time, sys, os
from naoqi import *

robotIP = "127.0.0.1"

def StiffnessOn(proxy):
    # We use the "Body" name to signify the collection of all joints
    pNames = "Body"
    pStiffnessLists = 0.0
    pTimeLists = 1.0
    proxy.stiffnessInterpolation(pNames, pStiffnessLists, pTimeLists)


def marche(xValue):

    # Init proxies.
    motionProxy = ALProxy("ALMotion", robotIP, 9559)
    postureProxy = ALProxy("ALRobotPosture", robotIP, 9559)

    # Set NAO in Stiffness On
    StiffnessOn(motionProxy)

    # Send NAO to Pose Init
    postureProxy.goToPosture("StandInit", 0.4)


    # TARGET VELOCITY
    X         = 0.5
    Y         = -0.057
    Theta     = 0.0
    Frequency = 0.0
    iniTime = time.time()
    motionProxy.setWalkTargetVelocity(X, Y, Theta, Frequency, [["MaxStepX", 0.06]])
    time.sleep(1)
    condition = 0
    xPos=0.0
    instanTime = 0
    while (xPos < xValue):
        Vx = motionProxy.getRobotVelocity()[0]
        pasTime = instanTime
        instanTime=time.time()-iniTime
        xPosPas = Vx * (instanTime-pasTime)
        xPos = xPos + xPosPas
        print xPos
    motionProxy.stopMove()
    postureProxy.goToPosture("StandInit", 1.0)

def BougeTaTete(angle):
    # Init proxies.
    motionProxy = ALProxy("ALMotion", robotIP, 9559)
    postureProxy = ALProxy("ALRobotPosture", robotIP, 9559)
    memoryProxy = ALProxy("ALMemory", robotIP, 9559)

    # Set NAO in Stiffness On
    StiffnessOn(motionProxy)
    a=postureProxy.getPostureFamily()
    print a
    # Send NAO to Pose Init if necessary
    while str(a)!="Standing":
        postureProxy.goToPosture("StandInit", 1.0)
        a=postureProxy.getPostureFamily()
        print a

    motionProxy.setStiffnesses("Body", 1.0)
    motionProxy.setAngles("HeadYaw", angle*math.pi/180, 0.4)

def Virage(angle):
    # Init proxies.
    motionProxy = ALProxy("ALMotion", robotIP, 9559)
    postureProxy = ALProxy("ALRobotPosture", robotIP, 9559)

    # Set NAO in Stiffness On
    StiffnessOn(motionProxy)

    # Send NAO to Pose Init
    postureProxy.goToPosture("StandInit", 0.4)


    x         = 0
    y         = 0
    theta     = angle*math.pi/180
    motionProxy.post.moveTo(x, y, theta)
    # Wait for it to finish
    motionProxy.waitUntilMoveIsFinished()
    motionProxy.stopMove()
    postureProxy.goToPosture("StandInit", 1.0)

if __name__ == "__main__":
#       marche(0.5)
        BougeTaTete(int(sys.argv[1]))
#       Virage(90)
