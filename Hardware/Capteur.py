import time
from Naoqi import *

IP = "127.0.0.1"

memoryProxy = ALProxy("ALMemory", IP, 9559)
sonarProxy = ALProxy("ALSonar", ip, 9559)

def getBatteryCharge():
    return memoryProxy.getData("Device/SubDeviceList/Battery/Current/Sensor/Value")


def SonarLeftRight():    
    sonarProxy.subscribe("myApplication")
    leftFirstEcho  = memoryProxy.getData("Device/SubDeviceList/US/Left/Sensor/Value")
    RightFirstEcho = memoryProxy.getData("Device/SubDeviceList/US/Right/Sensor/Value")
    return (leftFirstEcho, RightFirstEcho)


def Sonar():
    
    sonarProxy.subscribe("myApplication")
    return memoryProxy.getData("Device/SubDeviceList/US/Sensor/Value")


def Piezo():
    LfrontLeft = memoryProxy.getData("Device/SubDeviceList/LFoot/FSR/FrontLeft/Sensor/Value")
    LfrontRight= memoryProxy.getData("Device/SubDeviceList/LFoot/FSR/FrontRight/Sensor/Value")
    LrearLeft  = memoryProxy.getData("Device/SubDeviceList/LFoot/FSR/RearLeft/Sensor/Value")
    LrearRight = memoryProxy.getData("Device/SubDeviceList/LFoot/FSR/RearRight/Sensor/Value")
    Ltotal     = memoryProxy.getData("Device/SubDeviceList/LFoot/FSR/TotalWeight/Sensor/Value")
    RfrontLeft = memoryProxy.getData("Device/SubDeviceList/RFoot/FSR/FrontLeft/Sensor/Value")
    RfrontRight= memoryProxy.getData("Device/SubDeviceList/RFoot/FSR/FrontRight/Sensor/Value")
    RrearLeft  = memoryProxy.getData("Device/SubDeviceList/RFoot/FSR/RearLeft/Sensor/Value")
    RrearRight = memoryProxy.getData("Device/SubDeviceList/RFoot/FSR/RearRight/Sensor/Value")
    Rtotal     = memoryProxy.getData("Device/SubDeviceList/RFoot/FSR/TotalWeight/Sensor/Value")
    
def Temperature():
    TempList =[TBatt           = memoryProxy.getData("Device/SubDeviceList/Battery/Temperature/Sensor/Value"),
    THeadPitch      = memoryProxy.getData("Device/SubDeviceList/HeadPitch/Temperature/Sensor/Value"),
    THeadYaw        = memoryProxy.getData("Device/SubDeviceList/HeadYaw/Temperature/Sensor/Value"),
    TChevilleGPitch = memoryProxy.getData("Device/SubDeviceList/LAnklePitch/Temperature/Sensor/Value"),
    TChevilleGRoll  = memoryProxy.getData("Device/SubDeviceList/LAnkleRoll/Temperature/Sensor/Value"),
    TCoudeGRoll     = memoryProxy.getData("Device/SubDeviceList/LElbowRoll/Temperature/Sensor/Value"),
    TCoudeGYaw      = memoryProxy.getData("Device/SubDeviceList/LElbowYaw/Temperature/Sensor/Value"),
    TMainG          = memoryProxy.getData("Device/SubDeviceList/LHand/Temperature/Sensor/Value"),
    THancheGPitch   = memoryProxy.getData("Device/SubDeviceList/LHipPitch/Temperature/Sensor/Value"),
    THancheGRoll    = memoryProxy.getData("Device/SubDeviceList/LHipRoll/Temperature/Sensor/Value"),
    THancheGYaw     = memoryProxy.getData("Device/SubDeviceList/LHipYawPitch/Temperature/Sensor/Value"),
    TGenouGPitch    = memoryProxy.getData("Device/SubDeviceList/LKneePitch/Temperature/Sensor/Value"),
    TEpauleGPitch   = memoryProxy.getData("Device/SubDeviceList/LShoulderPitch/Temperature/Sensor/Value"),
    TEpauleGRoll    = memoryProxy.getData("Device/SubDeviceList/LShoulderRoll/Temperature/Sensor/Value"),
    TPoignetGYaw    = memoryProxy.getData("Device/SubDeviceList/LWristYaw/Temperature/Sensor/Value"),   
    TChevilleDPitch = memoryProxy.getData("Device/SubDeviceList/RAnklePitch/Temperature/Sensor/Value"),
    TChevilleDRoll  = memoryProxy.getData("Device/SubDeviceList/RAnkleRoll/Temperature/Sensor/Value"),
    TCoudeDRoll     = memoryProxy.getData("Device/SubDeviceList/RElbowRoll/Temperature/Sensor/Value"),
    TCoudeDYaw      = memoryProxy.getData("Device/SubDeviceList/RElbowYaw/Temperature/Sensor/Value"),
    TMainD          = memoryProxy.getData("Device/SubDeviceList/RHand/Temperature/Sensor/Value"),
    THancheDPitch   = memoryProxy.getData("Device/SubDeviceList/RHipPitch/Temperature/Sensor/Value"),
    THancheDRoll    = memoryProxy.getData("Device/SubDeviceList/RHipRoll/Temperature/Sensor/Value"),
    TGenouDPitch    = memoryProxy.getData("Device/SubDeviceList/RKneePitch/Temperature/Sensor/Value"),
    TEpauleDPich    = memoryProxy.getData("Device/SubDeviceList/RShoulderPitch/Temperature/Sensor/Value"),
    TEpauleDRoll    = memoryProxy.getData("Device/SubDeviceList/RShoulderRoll/Temperature/Sensor/Value"),
    TPoignetDYaw    = memoryProxy.getData("Device/SubDeviceList/RWristYaw/Temperature/Sensor/Value")]
