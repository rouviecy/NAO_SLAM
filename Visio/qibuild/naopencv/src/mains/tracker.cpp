/*
 * @(#)		tracker.cpp
 * @version	2.0
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Suivi d'un objet par segmentation de couleurs
 */

#include "../NAO_flux.h"
#include "../Head.h"
#include "../common/Blobs.h"
#include "../common/struct_HSV_bound.h"

#define	IP	"127.0.0.1"

using namespace std;

int main(){

	char key = 'a';		// clef de contrôle du programme
	float cx_head = 0.2;	// coefficient bangbang d'asservissement de la tête selon x
	float cy_head = 0.2;	// coefficient bangbang d'asservissement de la tête selon y
	float t_head = 0.3;	// constante de temps d'asservissement de la tête
	NAO_flux flux(		// initialisation du flux caméra
		IP,		// adresse IP du robot
		1,		// | 0 : QQVGA | 1 : QVGA | 2 : VGA | 3 : 4VGA |
		100,		// 100ms entre chaque image
		3,		// force du flou de lissage
		1);		// flip ... | 0 : aucun | 1 : selon x | 2 : selon y | 3 : selon x et y |
	Head head(IP);		// contrôle de la tête
	Blobs blobs;		// reconnaissance de blobs

	// limites de filtrage HSV
	STRUCT_HSV_BOUND* seuil = (STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	seuil->H_min = 2;	seuil->S_min = 150;	seuil->V_min = 120;	seuil->nb_dilate = 5;	seuil->seuil = 4;
	seuil->H_max = 14;	seuil->S_max = 255;	seuil->V_max = 255;	seuil->nb_erode = 5;
	blobs.Definir_limites_separation(seuil);

	// début de stiffness
	head.Rigide(true);

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		flux.Update();
		blobs.Set_img(flux.Get_next_top());
		blobs.Separer();
		blobs.Trouver_blobs();
		float dx = blobs.Get_best_x_rel();
		float dy = blobs.Get_best_y_rel();
		double aire = blobs.Get_best_area();
		head.Target_dx_rel(cx_head * dx, t_head);
		head.Target_dy_rel(cy_head * dy, t_head);

	}


	return 0;

}
