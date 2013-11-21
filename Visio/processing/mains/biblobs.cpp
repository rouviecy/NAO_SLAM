/*
 * @(#)		main.cpp
 * @version	1.4
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Détection de blobs sophistiqués (disque dans un autre disque)
 */

#include "../Gui.h"
#include "../Flux_cam.h"
#include "../Blobs.h"
#include "../Tracking.h"
#include "../Reco.h"

using namespace std;

int main(){

	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(-1, 40, 1, 3);		// initialisation du flux webcam (/dev/video0)
	Blobs blobs(5), blobs2(5);		// séparateur de blobs
	Tracking tracking(500), tracking2(500);	// suivi de blobs
	Gui gui;				// IHM
	gui.Creer_trackbar_HSV_sep("Separateur 1");
	gui.Creer_trackbar_HSV_sep2("Separateur 2");
	Reco reco;

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
		// suivre les blobs 1
		tracking.Set_img_prev(flux.Get_prev());
		tracking.Set_img_next(flux.Get_next());
		tracking.Set_amers(blobs.Get_mc());
		tracking.Tracker();
		// suivre les blobs 2
		tracking2.Set_img_prev(flux.Get_prev());
		tracking2.Set_img_next(flux.Get_next());
		tracking2.Set_amers(blobs2.Get_mc());
		tracking2.Tracker();
		// tester l'inclusion des blobs
		reco.Set_blobs_1(blobs.Get_mc());
		reco.Set_blobs_2(blobs2.Get_mc());
		// afficher le résultat
		gui.Ajouter_vecteurs("Video separateur 1", blobs.Get_img_blobs(), tracking.Get_amers(), tracking.Get_nv());
		gui.Ajouter_vecteurs("Video separateur 2", blobs2.Get_img_blobs(), tracking2.Get_amers(), tracking2.Get_nv());
		vector <cv::Point2f> points = reco.Test_inclusion(10);
		gui.Ajouter_vecteurs("Video multiblobs", flux.Get_cam(), points, points);
		
	}


	return 0;

}
