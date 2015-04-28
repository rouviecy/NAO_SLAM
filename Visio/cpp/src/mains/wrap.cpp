/*
 * @(#)		wrap.cpp
 * @version	1.4
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Appliquer une transformation perspective selon des paramètres sélectionnés par trackbars
 */

#include "../Gui.h"
#include "../Flux_cam.h"
#include "../Transfo.h"

using namespace std;

int main(){

	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(-1, 40, 1, 3, 0);		// initialisation du flux webcam (/dev/video0)
	Gui gui;				// IHM
	gui.Creer_trackbar_transfo("Wrappeur");
	Transfo transfo;

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		// mettre à jour les images du flux
		flux.Update();
		// afficher le résultat
		gui.Afficher_image("Video brute", flux.Get_cam());
		// transformation
		transfo.Set_img(flux.Get_cam());
		transfo.Definir_parametres_transformation(gui.Get_wrap_bound());
		transfo.Appliquer_wrap_from_structure();
		gui.Afficher_image("Transfo", transfo.Get_img_wrap());
	}
	return 0;

}
