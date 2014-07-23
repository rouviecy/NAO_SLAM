/*
 * @(#)		biblobs.cpp
 * @version	1.4
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Détection de blobs sophistiqués (disque dans un autre disque)
 */

#include "../../Gui.h"
#include "../../Flux_cam.h"
#include "../../Blobs.h"
#include "../../Reco.h"

using namespace std;

int main(){

	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(-1, 40, 1, 3, 1);		// initialisation du flux webcam (/dev/video0)
	Blobs blobs, blobs2;			// séparateur de blobs
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
		// tester l'inclusion des blobs
		reco.Set_blobs_1(blobs.Get_mc());
		reco.Set_blobs_2(blobs2.Get_mc());
		reco.Set_size(flux.Get_cam().size());
		vector <cv::Point2i> points = reco.Test_inclusion(10);
		// afficher le résultat
		gui.Afficher_image("Video separateur 1", blobs.Get_img_blobs());
		gui.Afficher_image("Video separateur 2", blobs2.Get_img_blobs());
		gui.Ajouter_vecteurs("Video multiblobs", flux.Get_cam(), points, points);
		
	}


	return 0;

}
