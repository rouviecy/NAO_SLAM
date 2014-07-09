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
#include "../../Transfo.h"
#include "../../Reco.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <string>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

int main(){

	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(-1, 40, 1, 3, 0);		// initialisation du flux webcam (/dev/video0)
	Gui gui;				// IHM
	Transfo transfo;
	Reco reco;
	int compteur = 0;

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		// mettre à jour les images du flux
		flux.Update();
		cv::Mat flou;
//		cv::blur(flux.Get_cam(), flou, cv::Size(9, 9));
flux.Get_cam().copyTo(flou);
		// détecter le quadrillage
		reco.Set_img(flou);
		reco.Detecter_quadrillage();
		if(key == 's'){
			mkdir(("./output/" + to_string(compteur)).c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
			vector <cv::Vec8i> liste_quad = reco.Get_quadrillage();
			for(size_t i = 0; i < liste_quad.size(); i++){
				vector <cv::Point2f> quadrille;
				quadrille.push_back(cv::Point2f(liste_quad[i][0], liste_quad[i][1]));
				quadrille.push_back(cv::Point2f(liste_quad[i][2], liste_quad[i][3]));
				quadrille.push_back(cv::Point2f(liste_quad[i][4], liste_quad[i][5]));
				quadrille.push_back(cv::Point2f(liste_quad[i][6], liste_quad[i][7]));
				// transformation
				transfo.Set_img(flux.Get_cam());
				transfo.Set_pts_redressement(quadrille);
				transfo.Appliquer_wrap(4, cv::Size(50, 50));
				imwrite("./output/" + to_string(compteur) + "/img_" + to_string(i) + ".png", transfo.Get_img_wrap());
			}
			key = 'a';
			compteur++;
		}
		// afficher le résultat
		gui.Afficher_image("Video quadrillage", reco.Get_img_quadrillage());
	}
	return 0;

}
