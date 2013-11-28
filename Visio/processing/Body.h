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
	void Set_img(cv::Mat img);

private:

	STRUCT_HSV_BOUND *hsv_jaune;
	STRUCT_HSV_BOUND *hsv_vert;
	STRUCT_HSV_BOUND *hsv_rouge;
	STRUCT_HSV_BOUND *hsv_bleu;

	STRUCT_HSV_BOUND *hsv1_L_hand, *hsv2_L_hand;
	STRUCT_HSV_BOUND *hsv1_R_hand, *hsv2_R_hand;
	STRUCT_HSV_BOUND *hsv1_L_foot, *hsv2_L_foot;
	STRUCT_HSV_BOUND *hsv1_R_foot, *hsv2_R_foot;

	cv::Mat img;

	Reco reco;
	Blobs blobs;

	void Couleurs();
	void Membres();

};

#endif
