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
#include "../../struct_vignette.h"

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main(int argc, char *argv[]){

	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(-1, 40, 1, 3, 0);		// initialisation du flux webcam (/dev/video0)
	Gui gui;				// IHM
	Transfo transfo;
	Reco reco;
	IO_file io;
	Tracking tracking(40);
	int compteur = 0;
	int force_blur = atoi(argv[1]);
	cv::Size kernel_blur(force_blur, force_blur);

	vector <STRUCT_VIGNETTE> liste_vignettes;

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
		if(key == 's'){
			mkdir(("./output/" + to_string(compteur)).c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
			vector <cv::Vec8i> liste_quad = reco.Get_quadrillage();
			for(size_t i = 0; i < liste_quad.size(); i++){
				STRUCT_VIGNETTE vignette;
				vector <cv::Point2f> quadrille;
				vignette.A = cv::Point2f(liste_quad[i][0], liste_quad[i][1]);	quadrille.push_back(vignette.A);
				vignette.B = cv::Point2f(liste_quad[i][2], liste_quad[i][3]);	quadrille.push_back(vignette.B);
				vignette.C = cv::Point2f(liste_quad[i][4], liste_quad[i][5]);	quadrille.push_back(vignette.C);
				vignette.D = cv::Point2f(liste_quad[i][6], liste_quad[i][7]);	quadrille.push_back(vignette.D);
				// transformation
				transfo.Set_img(flux.Get_cam());
				transfo.Set_pts_redressement(quadrille);
				transfo.Appliquer_wrap_from_pts_input(4, cv::Size(200, 200), cv::Size(10, 10));
				transfo.Get_img_wrap().copyTo(vignette.image);
				liste_vignettes.push_back(vignette);
				imwrite("./output/" + to_string(compteur) + "/img_" + to_string(i) + ".png", vignette.image);
			}

/*			liste_vignettes[0].index = 0;
			liste_vignettes[0].x = 0;
			liste_vignettes[0].y = 0;
			liste_vignettes[0].orientation = 0;
*/
			key = 'a';
			compteur++;
		}
		// afficher le résultat
		gui.Afficher_image("Video quadrillage", reco.Get_img_quadrillage());
	}
	return 0;

}
