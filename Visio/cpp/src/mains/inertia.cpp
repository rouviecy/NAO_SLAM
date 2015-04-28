/*
 * @(#)		inertia.cpp
 * @version	1.0
 * @autor	C. Rouvière
 */

 /**
 * Programme d'exploitation des images par OpenCV
 *	- Calcul de moyenne d'images consécutives
 */

#include <opencv2/opencv.hpp>
#include "../Gui.h"
#include "../Flux_cam.h"

#define	TAILLE_BUFFER	5	

using namespace std;

int main(){

	char key = 'a';				// clef de contrôle du programme
	Flux_cam flux(0, 40, 1, 3, 1);		// initialisation du flux webcam (/dev/video0)
	Gui gui;				// IHM

	int index = 0;
	bool complet = false;
	cv::Mat img[TAILLE_BUFFER];

	// boucle d'exécution : appuyer sur 'q' pour quitter
	while(key != 'q'){
		key = flux.Get_key();
		flux.Update();
		flux.Get_cam().convertTo(img[index], CV_16UC3);
		if(complet){
			cv::Mat somme(img[index].size(), CV_16UC3);
			for(int i = 0; i < TAILLE_BUFFER; i++){
				somme += img[i];
			}
			somme = (1./TAILLE_BUFFER) * somme;
			cv::Mat moyenne;
			somme.convertTo(moyenne, CV_8UC3);
			imshow("test", moyenne);
		}
		index++;
		if(index == TAILLE_BUFFER){
			index = 0;
			complet = true;
		}
	}

	return 0;

}
