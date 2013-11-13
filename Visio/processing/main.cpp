/*
 * @(#)		main.cpp
 * @version	1.3
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *
 */

#include "Gui.h"
#include "Flux_cam.h"
#include "Blobs.h"
#include "Tracking.h"
#include "Transfo.h"
#include "Calibrate.h"

using namespace std;

int main(){

	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(-1, 40, 1, 3);		// initialisation du flux webcam (/dev/video0)
	Blobs blobs(5);				// séparateur de blobs
	Tracking tracking(500);			// suivi de blobs
	Gui gui;				// IHM
	gui.Creer_trackbar_HSV_sep("Separateur");
	gui.Creer_trackbar_transfo("Transfo");
	Transfo transfo;
	Calibrate calib(cv::Size(9, 6));
	int nb_calib = 0;

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		// mettre à jour les images du flux
		flux.Update();
		// séparer les blobs
/*		blobs.Set_img(flux.Get_prev());
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
		// contrôler la souris
//		if(key != 'c'){gui.Controler_souris(blobs.Get_mc(), blobs.Get_img_blobs().size().width, blobs.Get_img_blobs().size().height);}
		// transformation
		transfo.Set_img(flux.Get_cam());
//		transfo.Definir_parametres_transformation(gui.Get_wrap_bound());
		transfo.Set_pts_redressement(blobs.Get_mc());
		transfo.Appliquer_wrap();
		gui.Afficher_image("Transfo", transfo.Get_img_wrap());
		if(key != 'c'){gui.Controler_souris(transfo.Get_center(), flux.Get_cam().size().width, flux.Get_cam().size().height);}
*/		if(nb_calib < 20){nb_calib = calib.Ajouter_img_calib(flux.Get_cam());}
		else if(nb_calib == 20){
			calib.Calibrer(flux.Get_cam().size());
			nb_calib++;
		}
		else{
			calib.Set_img(flux.Get_cam());
			gui.Afficher_image("Image calibrée", calib.Get_img());
		}
	}


	return 0;

}
