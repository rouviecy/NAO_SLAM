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

	void Detecter_tete();
	void Detecter_epaule_gauche();
	void Detecter_epaule_droite();
	void Detecter_coude_gauche();
	void Detecter_coude_droit();
	void Detecter_main_gauche();
	void Detecter_main_droite();
	void Detecter_pied_gauche();
	void Detecter_pied_droit();
	void Set_img(cv::Mat img);
	void Set_size(int width, int height);
	cv::Point2f Get_Head();
	cv::Point2f Get_L_shoulder();
	cv::Point2f Get_R_shoulder();
	cv::Point2f Get_L_elbow();
	cv::Point2f Get_R_elbow();
	cv::Point2f Get_L_hand();
	cv::Point2f Get_R_hand();
	cv::Point2f Get_L_foot();
	cv::Point2f Get_R_foot();

private:

	STRUCT_HSV_BOUND *hsv_jaune;
	STRUCT_HSV_BOUND *hsv_vert;
	STRUCT_HSV_BOUND *hsv_rouge;
	STRUCT_HSV_BOUND *hsv_bleu;
	STRUCT_HSV_BOUND *hsv_rose;

	STRUCT_HSV_BOUND *hsv_Tete[2];
	STRUCT_HSV_BOUND *hsv_L_shoulder[2];
	STRUCT_HSV_BOUND *hsv_R_shoulder[2];
	STRUCT_HSV_BOUND *hsv_L_elbow[2];
	STRUCT_HSV_BOUND *hsv_R_elbow[2];
	STRUCT_HSV_BOUND *hsv_L_hand[2];
	STRUCT_HSV_BOUND *hsv_R_hand[2];
	STRUCT_HSV_BOUND *hsv_L_foot[2];
	STRUCT_HSV_BOUND *hsv_R_foot[2];

	int width, height;

	cv::Mat img;

	cv::Point2f Tete, L_shoulder, R_shoulder, L_elbow, R_elbow, L_hand, R_hand, L_foot, R_foot;

	Reco reco;
	Blobs *blobs;

	void Couleurs();
	void Membres();
	std::vector <cv::Point2f> Update_blobs();

};

#endif
