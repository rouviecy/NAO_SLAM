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
#include <alproxies/alrobotposeproxy.h>

// Common includes
#include <iostream>

class Move{

public:

	Move(const char* ip);			// constructeur : avec adresse IP du robot concerné

	void Reconfigurer(			// à appeler avant le début de marche, et après la fin
		const bool arms,		// s'il faut utiliser les bras en balancier
		const bool enable_move);	// activer/désactiver les mouvements
	void Rigide(const bool etat);		// setter sur la stiffness
	void Vitesse(				// modifier la vitesse de déplacement du robot
		const float x,			// vitesse dans l'axe (de 0.0 à 1.0)
		const float y,			// vitesse latérale (de 0.0 à 1.0)
		const float theta,		// vitesse de rotation (en radians)
		const float frequency);		// fréquence du mouvement (entre 0.0 et 1.0)
	void Pose(				// modifier la posture
		const char* posture,		// "Stand" "Sit" "Crouch" "Knee" "Back"
		float vitesse);			// vitesse pour atteindre cette posture (entre 0.0 et 1.0)
	std::string Get_pose();			// getter sur la posture

private:

	AL::ALMotionProxy	motion_proxy;
	AL::ALRobotPostureProxy	posture_proxy;
	AL::ALRobotPoseProxy	pose_proxy;

	bool is_rigide;

};

#endif
