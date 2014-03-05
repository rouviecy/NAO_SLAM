#include "Head.h"

using namespace std;
using namespace AL;

// Constructeur
Head::Head(const char* ip){
	tete_x = "HeadYaw";
	tete_y = "HeadPitch";
	try{
		proxy = ALMotionProxy(ip, 9559);
	}catch(const ALError& e){
		std::cerr << "Caught exception: " << e.what() << std::endl;
		exit(1);
	}
	is_rigide = false;
}

// Contrôle de stiffness
void Head::Rigide(bool etat){
	if(etat){
		proxy.stiffnessInterpolation(tete_x, 1.0f, 1.0f);
		proxy.stiffnessInterpolation(tete_y, 1.0f, 1.0f);
	}
	else{
		proxy.stiffnessInterpolation(tete_x, 0.0f, 1.0f);
		proxy.stiffnessInterpolation(tete_y, 0.0f, 1.0f);
	}
	is_rigide = etat;
}

// Nouvel objectif en coordonnées absolues
void Head::Target_x_abs(float x_rad, float duree){Control(tete_x, true, x_rad, duree);}
void Head::Target_y_abs(float y_rad, float duree){Control(tete_y, true, y_rad, duree);}

// Nouvel objectif en coordonnées relatives
void Head::Target_dx_rel(float dx_rad, float duree){Control(tete_x, false, dx_rad, duree);}
void Head::Target_dy_rel(float dy_rad, float duree){Control(tete_y, false, dy_rad, duree);}

// Contrôle de la tête
void Head::Control(AL::ALValue joint, bool absolute, float value, float time){
	if(!is_rigide){Rigide(true);}
	ALValue targetAngle = ALValue::array(value);
	ALValue targetTime = ALValue::array(time);
	proxy.angleInterpolation(joint, targetAngle, targetTime, absolute);
}

// Guetters
float Head::Get_x(){return proxy.getAngles(tete_x, true)[0];}
float Head::Get_y(){return proxy.getAngles(tete_y, true)[0];}
