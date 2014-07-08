/*
 * @(#)		main.cpp
 * @version	1.4
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Détection et reliage de blobs
 */

#include <opencv/cv.h>

#include "../../Gui.h"
#include "../../Flux_cam.h"
#include "../../Blobs.h"
#include "../../Tracking.h"
#include "../../Utils.h"

#define	SEUIL_DYNAMIQUE	5

using namespace std;

int main(){

	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(-1, 40, 1, 3, 1);		// initialisation du flux webcam (/dev/video0)
	Blobs blobs;				// séparateur de blobs
	Gui gui;				// IHM
	Tracking tracking(500);			// gestion temporelle
	gui.Creer_trackbar_HSV_sep("Separateur");

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
		// séparer les blobs statiques des blobs en mouvement
		tracking.Set_img_prev(flux.Get_prev());
		tracking.Set_img_next(flux.Get_next());
		tracking.Set_amers(blobs.Get_mc());
		tracking.Tracker();
		std::vector <cv::Point2f> pts_amers, pts_nv, pts_fixe, pts_dyn;
		pts_amers = tracking.Get_amers();
		pts_nv = tracking.Get_nv();
		for(size_t i = 0; i < pts_amers.size(); i++){
			int dist_c = Utils::Distance_carree(pts_amers[i].x, pts_amers[i].y, pts_nv[i].x, pts_nv[i].y);
			if(dist_c < SEUIL_DYNAMIQUE){
				pts_fixe.push_back(pts_amers[i]);
			}
			else{
				pts_dyn.push_back(pts_amers[i]);
			}
		}

		// relier les points
		std::vector <cv::Point2f> pts1, pts2;
		for(size_t i = 0; i < pts_fixe.size(); i++){
			for(size_t j = 0; j < pts_fixe.size(); j++){
				if(i != j){
					pts1.push_back(pts_fixe[i]);
					pts2.push_back(pts_fixe[j]);
				}
			}
		}
		for(size_t i = 0; i < pts_dyn.size(); i++){
			for(size_t j = 0; j < pts_dyn.size(); j++){
				if(i != j){
					pts1.push_back(pts_dyn[i]);
					pts2.push_back(pts_dyn[j]);
				}
			}
		}
		// afficher le résultat
		gui.Afficher_image("Video", flux.Get_prev());
		gui.Ajouter_vecteurs("Video pseudo3D", blobs.Get_img_blobs(), pts1, pts2);
	}


	return 0;

}
