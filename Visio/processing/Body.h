/*
 * @(#)		Body.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Classe de reconstruction de corps
 */

#ifndef BODY
#define BODY

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "Blobs.h"
#include "Reco.h"
#include "struct_HSV_bound.h"

class Body{

public:

	Body();
	~Body();

	void Detecter_main_gauche();
	void Detecter_main_droite();
	void Detecter_pied_gauche();
	void Detecter_pied_droit();
	void Set_img(cv::Mat img);

private:

	STRUCT_HSV_BOUND *hsv_jaune;
	STRUCT_HSV_BOUND *hsv_vert;
	STRUCT_HSV_BOUND *hsv_rouge;
	STRUCT_HSV_BOUND *hsv_bleu;

	STRUCT_HSV_BOUND *hsv_L_hand[2];
	STRUCT_HSV_BOUND *hsv_R_hand[2];
	STRUCT_HSV_BOUND *hsv_L_foot[2];
	STRUCT_HSV_BOUND *hsv_R_foot[2];

	cv::Mat img;

	cv::Point2f L_hand, R_hand, L_foot, R_foot;

	Reco reco;
	Blobs *blobs;

	void Couleurs();
	void Membres();
	std::vector <cv::Point2f> Update_blobs();

};

#endif
