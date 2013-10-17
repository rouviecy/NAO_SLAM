/*
 * @(#)		main.cpp
 * @version	1.0
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *
 */

#include "Gui.h"
#include "Flux_cam.h"
#include "Blobs.h"

using namespace std;

int main(){

	Flux_cam flux(-1, 40, CV_RGB2HSV, 3);	// initialisation du flux webcam (/dev/video0)
	Blobs blobs;				// séparateur de blobs
	Gui gui;				// IHM
	gui.Creer_trackbar_HSV_sep("Separateur");

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(flux.Get_key() != 'q'){
		// mettre à jour les images du flux
		flux.Update();
		// séparer les blobs
		blobs.Set_img(flux.Get_next());
		blobs.Separer();
		// afficher le résultat
		gui.Afficher_image("Video brute", blobs.Get_img_sep());
	}


	return 0;

}
