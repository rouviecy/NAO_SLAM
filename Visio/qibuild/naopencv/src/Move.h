/*
 * @(#)		Move.h
 * @version	2.0
 * @autor	C. Rouvière
 */

/**
 * Classe de gestion de la marche d'un NAO
 */

#ifndef MOVE
#define MOVE

// Aldebaran includes
#include <alerror/alerror.h>
#include <alproxies/almotionproxy.h>
#include <alproxies/alrobotpostureproxy.h>

// Common includes
#include <iostream>

class Move{

public:

	Move(const char* ip);
	void Rigide(const bool etat);
	void Vitesse(const float x, const float y, const float theta, const float frequency);
	void Pose(const char* posture, float vitesse);

private:

	AL::ALMotionProxy motion_proxy;
	AL::ALRobotPostureProxy posture_proxy;

	bool is_rigide;

};

#endif
