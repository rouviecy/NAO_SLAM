/*
 * @(#)		main.cpp
 * @version	1.4
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Contrôle de la souris avec un pointeur unique et clic
 */

#include "../../Gui.h"
#include "../../Flux_cam.h"
#include "../../Blobs.h"
#include "../../Tracking.h"

using namespace std;

int main(){

	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(-1, 40, 1, 3, 1);		// initialisation du flux webcam (/dev/video0)
	Blobs blobs, blobs2;			// séparateur de blobs
	Tracking tracking(500), tracking2(500);	// suivi de blobs
	Gui gui;				// IHM
	gui.Creer_trackbar_HSV_sep("Separateur_mouse");
	gui.Creer_trackbar_HSV_sep2("Separateur_clic");

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		// mettre à jour les images du flux
		flux.Update();
		// séparer les blobs mouse
		blobs.Set_img(flux.Get_prev());
		blobs.Definir_limites_separation(gui.Get_HSV_bound());
		blobs.Separer();
		blobs.Trouver_blobs();
		// séparer les blobs clic
		blobs2.Set_img(flux.Get_prev());
		blobs2.Definir_limites_separation(gui.Get_HSV_bound2());
		blobs2.Separer();
		blobs2.Trouver_blobs();
		// suivre les blobs mouse
		tracking.Set_img_prev(flux.Get_prev());
		tracking.Set_img_next(flux.Get_next());
		tracking.Set_amers(blobs.Get_mc());
		tracking.Tracker();
		// suivre les blobs clic
		tracking2.Set_img_prev(flux.Get_prev());
		tracking2.Set_img_next(flux.Get_next());
		tracking2.Set_amers(blobs2.Get_mc());
		tracking2.Tracker();
		// afficher le résultat
		gui.Afficher_image("Video brute", flux.Get_cam());
		gui.Ajouter_vecteurs("Video tracking mouse", blobs.Get_img_blobs(), tracking.Get_amers(), tracking.Get_nv());
		gui.Ajouter_vecteurs("Video tracking clic", blobs2.Get_img_blobs(), tracking2.Get_amers(), tracking2.Get_nv());
		// contrôler la souris
		if(key != 'c'){
			gui.Controler_souris(blobs.Get_mc(), blobs.Get_img_blobs().size().width, blobs.Get_img_blobs().size().height);
			gui.Cliquer(blobs2.Get_mc());
		}
	}


	return 0;

}
