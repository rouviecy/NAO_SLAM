/*
 * @(#)		tracker.cpp
 * @version	2.0
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Suivi d'un objet par segmentation de couleurs
 */

#include "NAO/NAO_flux.h"
#include "NAO/Head.h"
#include "NAO/Move.h"
#include "NAO/Leds.h"
#include "images/Blobs.h"
#include "images/struct_HSV_bound.h"

#define	IP	"127.0.0.1"

using namespace std;

int main(){

	char key = 'a';		// clef de contrôle du programme
	float cx_head = 0.2;	// coefficient d'asservissement de la tête selon x
	float cy_head = 0.2;	// coefficient d'asservissement de la tête selon y
	float t_head = 0.3;	// constante de temps d'asservissement de la tête
	float v = 0.9;		// vitesse de déplacement (bangbang)
	int seuil_max = 150;	// taille de la tâche au-delà de laquelle le robot reculera
	int seuil_mid = 100;	// taille de la tâche au-delà de laquelle le robot restera sur place
	int seuil_min = 4;	// taille de la tâche au-delà de laquelle le robot s'approchera
	NAO_flux flux(		// initialisation du flux caméra
		IP,		// adresse IP du robot
		1,		// | 0 : QQVGA | 1 : QVGA | 2 : VGA | 3 : 4VGA |
		100,		// 100ms entre chaque image
		3,		// force du flou de lissage
		1);		// flip ... | 0 : aucun | 1 : selon x | 2 : selon y | 3 : selon x et y |
	Head head(IP);		// contrôle de la tête
	Move move(IP);		// contrôle du mouvement
	Leds leds(IP);		// contrôle des LEDs
	Blobs blobs;		// reconnaissance de blobs

	// limites de filtrage HSV
	STRUCT_HSV_BOUND* seuil = (STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	seuil->H_min = 2;	seuil->S_min = 150;	seuil->V_min = 120;	seuil->nb_dilate = 5;	seuil->seuil = seuil_min;
	seuil->H_max = 14;	seuil->S_max = 255;	seuil->V_max = 255;	seuil->nb_erode = 5;
	blobs.Definir_limites_separation(seuil);

	// début de stiffness
	head.Rigide(true);
	move.Rigide(true);
	move.Reconfigurer(true, true);
	move.Pose("StandInit", 1.0);

	for(int i = 0; i < 100; i++){

		// traitement d'images
		key = flux.Get_key();
		flux.Update();
		blobs.Set_img(flux.Get_next_top());
		blobs.Separer();
		blobs.Trouver_blobs();

		// positionner la tête
		float dx = blobs.Get_best_x_rel();
		float dy = blobs.Get_best_y_rel();
		double aire = blobs.Get_best_area();
		float theta = 0;
		if (aire > 0){
			head.Target_dx_rel(cx_head * dx, t_head);
			head.Target_dy_rel(cy_head * dy, t_head);
			theta = head.Get_x() + dx;
		}

		// contrôler le mouvement de déplacement
		float vitesse = 0;
		if (theta < -0.9) {theta = -0.9;}
		if (theta > +0.9) {theta = +0.9;}
		if	(aire > seuil_max)				{vitesse = -v;}
		else if (aire > seuil_mid and aire <= seuil_min)	{vitesse = +v;}
		else if	(aire > seuil_mid and aire <= seuil_max){
			if (theta > -0.3 and theta < +0.3) {theta = 0;}
		}
		move.Vitesse(vitesse, 0., theta, 0.8);

		// contrôler les LEDs
		if (aire > 0)	{leds.Eye(255, 0, 0, 0, 0, 0.5);}
		else		{leds.Eye(0, 255, 0, 0, 0, 0.5);}

	}

	move.Pose("Sit", 1.0);
	move.Reconfigurer(true, false);
	move.Rigide(false);
	head.Rigide(false);

	return 0;

}
