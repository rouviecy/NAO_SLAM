#include "Speak.h"

using namespace std;
using namespace AL;

// Constructeur
Speak::Speak(const char* ip, bool english){
	try{
		proxy = ALTextToSpeechProxy(ip, 9559);
	}catch(const ALError& e){
		std::cerr << "Caught exception: " << e.what() << std::endl;
		exit(1);
	}
	if(english)	{proxy.setLanguage("English");}
	else		{proxy.setLanguage("French");}
}

// Parler
void Speak::Say(const char* text){proxy.say(text);}
