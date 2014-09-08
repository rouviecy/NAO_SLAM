/*
 * @(#)		metadonnees.cpp
 * @version	1.0
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Détecte un quadrillage, et enregistre les vignettes
 * 	- Gestion des métadonnées des vignettes
 * 	- Passer en argument la force du flou à appliquer au préalable
 */

#include "../../Gui.h"
#include "../../Flux_cam.h"
#include "../../Transfo.h"
#include "../../Tracking.h"
#include "../../Reco.h"
#include "../../IO_file.h"
#include "../../mapping/Carte.h"
#include "../../mapping/Multimap.h"

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main(int argc, char *argv[]){

	char key = 'a';								// clef de contrôle du programme
	Flux_cam flux(-2, 40, 1, 3, 3, argv[1]);	// initialisation du flux webcam (/dev/video0)
	Gui gui;									// IHM
	Transfo transfo;
	Reco reco;
	IO_file io;
	Carte carte;
	Multimap multimap;
	Tracking tracking(40);
	int compteur = 0;
	int force_blur = atoi(argv[2]);
	cv::Size kernel_blur(force_blur, force_blur);

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		// mettre à jour les images du flux
		flux.Update();
		cv::Mat flou;
		if(force_blur > 0){cv::blur(flux.Get_cam(), flou, kernel_blur);}
		else{flux.Get_cam().copyTo(flou);}
		// détecter le quadrillage
		reco.Set_img(flou);
		reco.Detecter_quadrillage();
		reco.Orienter_quadrillage();
		if(key == 's'){
			mkdir(("./output/" + to_string(compteur)).c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
			vector < vector <cv::Point2i> > liste_quadrillage = reco.Get_quadrillage();
			for(int i = 0; i < liste_quadrillage.size(); i++){
				// transformation
				cv::Mat img_redressee;
				transfo.Set_img(flux.Get_cam());
				transfo.Set_pts_redressement(liste_quadrillage[i]);
				transfo.Appliquer_wrap_from_pts_input(4, cv::Size(201, 201), cv::Size(10, 10));
				transfo.Get_img_wrap().copyTo(img_redressee);
				imwrite("./output/" + to_string(compteur) + "/img_" + to_string(i) + ".png", img_redressee);
				carte.Remplir_buffer(img_redressee, liste_quadrillage[i]);
			}
			carte.Traiter_buffer();
			multimap.Add_map(carte.Get_cases());
			multimap.Try_fusion();
			multimap.Show_maps();
			carte.Clear();
			key = 'a';
			compteur++;
		}
		// afficher le résultat
		gui.Afficher_image("Video quadrillage", reco.Get_img_quadrillage());
	}
	return 0;

}
