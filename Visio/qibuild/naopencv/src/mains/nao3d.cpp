/*
 * @(#)		nao3d.cpp
 * @version	2.0
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Reconstitution 3D du corps d'un NAO
 */

#include "../NAO_flux.h"
#include "../common/Body.h"

using namespace std;

int main(){

	char key = 'a';		// clef de contrôle du programme
	NAO_flux flux(		// initialisation du flux caméra
		"127.0.0.1",	// adresse IP du robot
		1,		// | 0 : QQVGA | 1 : QVGA | 2 : VGA | 3 : 4VGA |
		100,		// 100ms entre chaque image
		3,		// force du flou de lissage
		1);		// flip ... | 0 : aucun | 1 : selon x | 2 : selon y | 3 : selon x et y |
	Body body;

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		flux.Update();

		body.Set_img(flux.Get_next_top());
		body.Detecter_tete();
		body.Detecter_torse_haut();		body.Detecter_torse_bas();
		body.Detecter_epaule_gauche();		body.Detecter_epaule_droite();
		body.Detecter_coude_gauche();		body.Detecter_coude_droit();
		body.Detecter_main_gauche();		body.Detecter_main_droite();
		body.Detecter_genou_gauche();		body.Detecter_genou_droit();
		body.Detecter_pied_gauche();		body.Detecter_pied_droit();

		std::vector <cv::Point2f> liste1;
		std::vector <cv::Point2f> liste2;
		liste1.push_back(body.Get_Head());		liste2.push_back(body.Get_T_torso());
		liste1.push_back(body.Get_T_torso());		liste2.push_back(body.Get_L_shoulder());
		liste1.push_back(body.Get_T_torso());		liste2.push_back(body.Get_R_shoulder());
		liste1.push_back(body.Get_L_shoulder());	liste2.push_back(body.Get_L_elbow());
		liste1.push_back(body.Get_R_shoulder());	liste2.push_back(body.Get_R_elbow());
		liste1.push_back(body.Get_L_elbow());		liste2.push_back(body.Get_L_hand());
		liste1.push_back(body.Get_R_elbow());		liste2.push_back(body.Get_R_hand());
		liste1.push_back(body.Get_T_torso());		liste2.push_back(body.Get_B_torso());
		liste1.push_back(body.Get_B_torso());		liste2.push_back(body.Get_L_knee());
		liste1.push_back(body.Get_B_torso());		liste2.push_back(body.Get_R_knee());
		liste1.push_back(body.Get_L_knee());		liste2.push_back(body.Get_L_foot());
		liste1.push_back(body.Get_R_knee());		liste2.push_back(body.Get_R_foot());
	}


	return 0;

}
