#include "Leds.h"

using namespace std;
using namespace AL;

// Constructeur
Leds::Leds(const char* ip){
	try{
		proxy = ALLedsProxy(ip, 9559);
	}catch(const ALError& e){
		std::cerr << "Caught exception: " << e.what() << std::endl;
		exit(1);
	}
	Liste();
}

// Liste des LEDs
void Leds::Liste(){

	name_eye[0][0] = "FaceLeds";	name_eye[1][0] = "LeftFaceLeds";	name_eye[2][0] = "RightFaceLeds";
	name_eye[0][1] = "FaceLed1";	name_eye[1][1] = "LeftFaceLed1";	name_eye[2][1] = "RightFaceLed1";
	name_eye[0][2] = "FaceLed2";	name_eye[1][2] = "LeftFaceLed2";	name_eye[2][2] = "RightFaceLed2";
	name_eye[0][3] = "FaceLed3";	name_eye[1][3] = "LeftFaceLed3";	name_eye[2][3] = "RightFaceLed3";
	name_eye[0][4] = "FaceLed4";	name_eye[1][4] = "LeftFaceLed4";	name_eye[2][4] = "RightFaceLed4";
	name_eye[0][5] = "FaceLed5";	name_eye[1][5] = "LeftFaceLed5";	name_eye[2][5] = "RightFaceLed5";
	name_eye[0][6] = "FaceLed6";	name_eye[1][6] = "LeftFaceLed6";	name_eye[2][6] = "RightFaceLed6";
	name_eye[0][7] = "FaceLed7";	name_eye[1][7] = "LeftFaceLed7";	name_eye[2][7] = "RightFaceLed7";
	name_eye[0][8] = "FaceLed8";	name_eye[1][8] = "LeftFaceLed8";	name_eye[2][8] = "RightFaceLed8";

	name_ear[0] = "EarLeds";	name_ear[1] = "LeftEarLeds";		name_ear[2] = "RightEarLeds";

	name_brain[0] = "BrainLeds";	name_brain[1] = "BrainLedsLeft";	name_brain[2] = "BrainLedsRight";

}

void Leds::Control(const std::string name, const int R, const int G, const int B, const float duree){
	int color = B + 256 * G + 65536 * R;
	proxy.fadeRGB(name, color, duree);
}

// Commande de toutes les LEDs
void Leds::All(const int R, const int G, const int B, const float duree){
	Control("AllLeds", R, G, B, duree);
}

// Commande des LEDs des yeux
void Leds::Eye(const int cote, const int numero, const int R, const int G, const int B, const float duree){
	if(cote >= 0 and cote <= 2 and numero >= 0 and numero <= 8){
		Control(name_eye[cote][numero], R, G, B, duree);
	}
}

// Commande des LEDs des oreilles
void Leds::Ear(const int cote, const int R, const int G, const int B, const float duree){
	if(cote >= 0 and cote <= 2){
		Control(name_ear[cote], R, G, B, duree);
	}
}

// Commande des LEDs du cerveau
void Leds::Brain(const int cote, const int R, const int G, const int B, const float duree){
	if(cote >= 0 and cote <= 2){
		Control(name_brain[cote], R, G, B, duree);
	}
}
