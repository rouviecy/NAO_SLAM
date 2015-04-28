/*
 * @(#)		flot_optique.cpp
 * @version	1.0
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Calcul de flot optique
 */

#include "../Gui.h"
#include "../Flux_cam.h"
#include "../Tracking.h"

using namespace std;

int main(){

	bool valide = false;
	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(0, 40, 1, 3, 1);		// initialisation du flux webcam (/dev/video0)
	Gui gui;				// IHM
	Tracking tracking(2000);

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		flux.Update();
		if(valide){
			tracking.Set_img_prev(flux.Get_prev());
			tracking.Set_img_next(flux.Get_next());
			tracking.GoodFeatures(2000);
			if(tracking.Tracker()){
				gui.Ajouter_vecteurs("Image", flux.Get_prev(), tracking.Get_amers(), tracking.Get_nv());
			}
		}
		else{
			valide = true;
		}
	}

	return 0;

}
