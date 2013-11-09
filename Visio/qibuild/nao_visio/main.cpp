/*
 * Copyright (c) 2012, 2013 Aldebaran Robotics. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the COPYING file.
 */
#include <iostream>
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>

int main(int argc, char* argv[]){
	if(argc != 2){
		std::cerr << "Wrong number of arguments!" << std::endl;
		std::cerr << "Usage: say NAO_IP" << std::endl;
		exit(2);
	}

	  /** The desired phrase to be said. */
	const std::string phraseToSay = "Hello world";
	try{
		AL::ALTextToSpeechProxy tts(argv[1], 9559);
		tts.say(phraseToSay);
	}catch(const AL::ALError& e){
		std::cerr << "Caught exception: " << e.what() << std::endl;
		exit(1);
	}
	exit(0);
}
