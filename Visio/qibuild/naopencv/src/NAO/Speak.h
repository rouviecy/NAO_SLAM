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

	Speak(				// Constructeur
		const char* ip,		// IP du robot concerné
		const bool english);	// | true : anglais | false : français |

	void Say(const char* text);	// Dire un texte

private:

	AL::ALTextToSpeechProxy proxy;

};

#endif
