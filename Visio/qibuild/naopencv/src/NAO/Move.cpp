#include "Move.h"

using namespace std;
using namespace AL;

// Constructeur
Move::Move(const char* ip){
	try{
		motion_proxy = ALMotionProxy(ip, 9559);
	}catch(const AL::ALError& e){
		std::cerr << "Caught exception: " << e.what() << std::endl;
		exit(1);
	}
	try{
		posture_proxy = ALRobotPostureProxy(ip, 9559);
	}catch(const AL::ALError& e){
		std::cerr << "Caught exception: " << e.what() << std::endl;
		exit(1);
	}
	is_rigide = false;
}

// Modifier les paramètres de marche
void Move::Reconfigurer(const bool arms, const bool enable_move){
	if(enable_move)	{motion_proxy.moveInit();}
	else		{motion_proxy.stopMove();}
	motion_proxy.setWalkArmsEnabled(arms, arms);
}

// Contrôle de stiffness
void Move::Rigide(const bool etat){
	if(etat){
		motion_proxy.stiffnessInterpolation("Body", 1.0f, 1.0f);
		motion_proxy.stiffnessInterpolation("Body", 1.0f, 1.0f);
	}
	else{
		motion_proxy.stiffnessInterpolation("Body", 0.0f, 1.0f);
		motion_proxy.stiffnessInterpolation("Body", 0.0f, 1.0f);
	}
	is_rigide = etat;
}

// Contrôle de mouvement
void Move::Vitesse(const float x, const float y, const float theta, const float frequency){
	if(!is_rigide){Rigide(true);}
	motion_proxy.setWalkTargetVelocity(x, y, theta, frequency);
}

// Contrôle de posture
void Move::Pose(const char* posture, float vitesse){
	if(!is_rigide){Rigide(true);}
	posture_proxy.goToPosture(posture, vitesse);
}
