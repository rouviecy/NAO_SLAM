/*
 * Copyright (c) 2012, 2013 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */
#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>
#include <alproxies/alvideodeviceproxy.h>
#include <alvision/alimage.h>
#include <alvision/alvisiondefinitions.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace AL;

int main(int argc, char* argv[]){
	if(argc != 2){
		cerr << "Wrong number of arguments!" << endl;
		cerr << "Usage: say NAO_IP" <<endl;
		exit(2);
	}

	const string IP = argv[1];
	const string phraseToSay = "Hello world";
	ALVideoDeviceProxy camProxy;
	string clientName;

	try{
		ALTextToSpeechProxy tts(IP, 9559);
		tts.say(phraseToSay);
	}catch(const AL::ALError& e){
		cerr << "Caught exception: " << e.what() << endl;
		exit(1);
	}

	try{
		camProxy = ALVideoDeviceProxy(IP, 9559);
		clientName = camProxy.subscribe("test", kQVGA, kBGRColorSpace, 30);
	}catch(const AL::ALError& e){
		cerr << "Caught exception: " << e.what() << endl;
		exit(1);
	}
	exit(0);
}
