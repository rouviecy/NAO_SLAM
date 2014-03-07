/*
 * @(#)		Speak.h
 * @version	2.0
 * @autor	C. Rouvière
 */

/**
 * Classe de gestion de la parole d'un NAO
 */

#ifndef SPEAK
#define SPEAK

// Aldebaran includes
#include <alerror/alerror.h>
#include <alproxies/altexttospeechproxy.h>

// Common includes
#include <iostream>

class Speak{

public:

	Speak(const char* ip, const bool english);
	void Say(const char* text);

private:

	AL::ALTextToSpeechProxy proxy;

};

#endif
