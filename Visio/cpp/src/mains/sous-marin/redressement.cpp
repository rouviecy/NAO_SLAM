/*
 * @(#)		redressement.cpp
 * @version	1.5
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Détecte un quadrillage, et enregistre les vignettes pour les reconnaître plus tard
 * 	- Passer en argument la force du flou à appliquer au préalable
 */

#include "../../Gui.h"
#include "../../Flux_cam.h"
#include "../../Transfo.h"
#include "../../Tracking.h"
#include "../../Reco.h"
#include "../../IO_file.h"

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
			vector <cv::Mat> liste_vignettes;
			vector < vector <cv::Point2i> > liste_quadrillage = reco.Get_quadrillage();
			for(int i = 0; i < liste_quadrillage.size(); i++){
				// transformation
				transfo.Set_img(flux.Get_cam());
				transfo.Set_pts_redressement(liste_quadrillage[i]);
				transfo.Appliquer_wrap_from_pts_input(4, cv::Size(200, 200), cv::Size(10, 10));
				cv::Mat img_redressee;
				transfo.Get_img_wrap().copyTo(img_redressee);
				liste_vignettes.push_back(img_redressee);
				imwrite("./output/" + to_string(compteur) + "/img_" + to_string(i) + ".png", liste_vignettes[i]);
			}
			for(int k = 0; k < compteur; k++){
				vector <STRUCT_NOM> liste = io.Lister_fichiers("./output/" + to_string(k), "png");
				for(size_t j = 0; j < liste.size(); j++){
					cout << liste[j].nom_complet << endl;
					cv::Mat old_img = cv::imread(liste[j].nom_complet);
					for(size_t i = 0; i < liste_vignettes.size() ; i++){
						tracking.Set_img_prev(old_img);
						tracking.Set_img_next(liste_vignettes[i]);
						if(tracking.Try_match(10, 5)){cout << "\tok avec " << k+1 << "-" << i << " avec orientation " << 90*tracking.Get_orientation() << "°" << endl;}
					}
				}
			}
			key = 'a';
			compteur++;
		}
		// afficher le résultat
		gui.Afficher_image("Video quadrillage", reco.Get_img_quadrillage());
	}
	return 0;

}
