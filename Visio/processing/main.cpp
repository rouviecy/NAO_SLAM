/*
 * @(#)		main.cpp
 * @version	1.2
 * @autor	C. Rouvière
 */

 /**
 * Programme d'odométrie visuelle
 *	- exploite les librairies d'OpenCV pour traiter des images ...
 */

#include "Gui.h"
#include "Flux_cam.h"

using namespace std;

int main(){

	Flux_cam flux(-1, 40, CV_RGB2GRAY, 3);	// initialisation du flux webcam (/dev/video0)
	Gui gui;				// IHM

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(flux.Get_key() != 'q'){
		// mettre à jour les images du flux
		flux.Update();
		// afficher le résultat
		gui.Afficher_image("Video brute", flux.Get_next());
	}

	return 0;

}
