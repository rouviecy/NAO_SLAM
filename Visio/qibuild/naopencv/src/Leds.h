/*
 * @(#)		Leds.h
 * @version	2.0
 * @autor	C. Rouvière
 */

/**
 * Classe de gestion des LEDs d'un NAO
 */

#ifndef LEDS
#define LEDS

// Aldebaran includes
#include <alerror/alerror.h>
#include <alproxies/alledsproxy.h>

// Common includes
#include <iostream>

class Leds{

public:

	Leds(const char* ip);
	void All(			// contrôle de toutes les LEDs
		const int R,		// composante rouge (0 à 255)
		const int G,		// composante verte (0 à 255)
		const int B,		// composante bleue (0 à 255)
		const float duree);	// durée de la transition (en secondes)
	void Eye(			// contrôle des LEDs des yeux
		const int cote,		// | 0 : tous | 1 : gauche | 2 : droite |
		const int numero,	// | 0 : tous | de 1 à 8 : numéro de la LED |
		const int R,		// composante rouge (0 à 255)
		const int G,		// composante verte (0 à 255)
		const int B,		// composante bleue (0 à 255)
		const float duree);	// durée de la transition (en secondes)
	void Ear(			// contrôle des LEDs des oreilles
		const int cote,		// | 0 : tous | 1 : gauche | 2 : droite |
		const int R,		// composante rouge (0 à 255)
		const int G,		// composante verte (0 à 255)
		const int B,		// composante bleue (0 à 255)
		const float duree);	// durée de la transition (en secondes)
	void Brain(			// contrôle des LEDs du cerveau
		const int cote,		// | 0 : tous | 1 : gauche | 2 : droite |
		const int R,		// composante rouge (0 à 255)
		const int G,		// composante verte (0 à 255)
		const int B,		// composante bleue (0 à 255)
		const float duree);	// durée de la transition (en secondes)

private:

	AL::ALLedsProxy proxy;
	std::string name_eye[3][9];
	std::string name_ear[3];
	std::string name_brain[3];

	void Liste();
	void Control(const std::string name, const int R, const int G, const int B, const float duree);

};

#endif
