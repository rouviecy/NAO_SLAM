/*
 * @(#)		histogramme.cpp
 * @version	1.0
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Visualiser l'histogramme d'un flux vidéo
 */

#include "../Gui.h"
#include "../Flux_cam.h"
#include "../Instruments.h"

using namespace std;

int main(){

	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(-1, 40, 1, 3, 0);		// initialisation du flux webcam (/dev/video0)
	Gui gui;				// IHM
	Instruments instrum(16 * 20, 300);

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		// mettre à jour les images du flux
		flux.Update();
		// récupérer l'histogramme
		instrum.Set_img(flux.Get_cam());
		instrum.Calculer_hist_H(16);
		// afficher le résultat
		gui.Afficher_image("Video brute", flux.Get_cam());
		gui.Afficher_image("Histogramme H", instrum.Get_hist_H());
	}
	return 0;

}
