/*
 * @(#)		main.cpp
 * @version	1.4
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Contrôle de la souris via plusieurs amers
 */

#include "../../Gui.h"
#include "../../Flux_cam.h"
#include "../../Blobs.h"
#include "../../Tracking.h"
#include "../../Transfo.h"

using namespace std;

int main(){

	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(1, 40, 1, 3, 0);		// initialisation du flux webcam (/dev/video0)
	Blobs blobs;				// séparateur de blobs
	Tracking tracking(500);			// suivi de blobs
	Gui gui;				// IHM
	gui.Creer_trackbar_HSV_sep("Separateur");
	Transfo transfo;

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		// mettre à jour les images du flux
		flux.Update();
		// séparer les blobs
		blobs.Set_img(flux.Get_prev());
		blobs.Definir_limites_separation(gui.Get_HSV_bound());
		blobs.Separer();
		blobs.Trouver_blobs();
		blobs.Relier();
		// suivre les blobs
		tracking.Set_img_prev(flux.Get_prev());
		tracking.Set_img_next(flux.Get_next());
		tracking.Set_amers(blobs.Get_mc());
		tracking.Tracker();
		// afficher le résultat
		gui.Afficher_image("Video brute", flux.Get_cam());
		gui.Ajouter_vecteurs("Video tracking", blobs.Get_img_blobs(), tracking.Get_amers(), tracking.Get_nv());
		// transformation
		transfo.Set_img(flux.Get_cam());
		transfo.Set_pts_redressement(blobs.Get_mc());
		transfo.Appliquer_wrap(5);
		gui.Afficher_image("Transfo", transfo.Get_img_wrap());
		if(key != 'c'){gui.Controler_souris(transfo.Get_center(), flux.Get_cam().size().width, flux.Get_cam().size().height);}	}

	return 0;

}
