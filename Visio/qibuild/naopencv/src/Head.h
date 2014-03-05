/*
 * @(#)		Head.h
 * @version	2.0
 * @autor	C. Rouvière
 */

/**
 * Classe de gestion de la tête d'un NAO
 */

#ifndef HEAD
#define HEAD

// Aldebaran includes
#include <alerror/alerror.h>
#include <alproxies/almotionproxy.h>

// Common includes
#include <iostream>

class Head{

public:

	Head(const char* ip);
	void Rigide(bool etat);
	void Target_x_abs(float x_rad, float duree);
	void Target_y_abs(float y_rad, float duree);
	void Target_dx_rel(float dx_rad, float duree);
	void Target_dy_rel(float dy_rad, float duree);

private:

	AL::ALMotionProxy proxy;
	AL::ALValue tete_x;
	AL::ALValue tete_y;

	bool is_rigide;

	void Control(AL::ALValue joint, bool absolute, float value, float time);

};

#endif
