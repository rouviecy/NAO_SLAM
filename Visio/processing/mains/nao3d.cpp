/*
 * @(#)		main.cpp
 * @version	1.4
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Reconstitution 3D du corps d'un NAO
 */

#include "../Gui.h"
#include "../Flux_cam.h"
#include "../Body.h"

using namespace std;

int main(){

	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(-1, 40, 1, 3, 1);		// initialisation du flux webcam (/dev/video0)
	Gui gui;				// IHM
	Body body;

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		// mettre à jour les images du flux
		flux.Update();

		gui.Afficher_image("video", flux.Get_cam());
		
	}


	return 0;

}