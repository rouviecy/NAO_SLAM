/*
 * @(#)		Body.h
 * @version	2.0
 * @autor	C. Rouvière
 */

/**
 * Classe de reconstruction de corps
 */

#ifndef BODY
#define BODY

#include <opencv2/core/core.hpp>
#include "Blobs.h"
#include "Reco.h"
#include "struct_HSV_bound.h"

class Body{

public:

	Body();
	~Body();

	void Detecter_tete();
	void Detecter_torse_haut();	void Detecter_torse_bas();
	void Detecter_epaule_gauche();	void Detecter_epaule_droite();
	void Detecter_coude_gauche();	void Detecter_coude_droit();
	void Detecter_main_gauche();	void Detecter_main_droite();
	void Detecter_genou_gauche();	void Detecter_genou_droit();
	void Detecter_pied_gauche();	void Detecter_pied_droit();
	void Set_img(const cv::Mat img);
	void Tester_position();
	cv::Point2f Get_Head();
	cv::Point2f Get_T_torso();	cv::Point2f Get_B_torso();
	cv::Point2f Get_L_shoulder();	cv::Point2f Get_R_shoulder();
	cv::Point2f Get_L_elbow();	cv::Point2f Get_R_elbow();
	cv::Point2f Get_L_hand();	cv::Point2f Get_R_hand();
	cv::Point2f Get_L_knee();	cv::Point2f Get_R_knee();
	cv::Point2f Get_L_foot();	cv::Point2f Get_R_foot();
	int Get_posture();

private:

	STRUCT_HSV_BOUND *hsv_jaune;
	STRUCT_HSV_BOUND *hsv_vert;
	STRUCT_HSV_BOUND *hsv_rose;
	STRUCT_HSV_BOUND *hsv_lavande;
	STRUCT_HSV_BOUND *hsv_turq;
	STRUCT_HSV_BOUND *hsv_beige;
	STRUCT_HSV_BOUND *hsv_mauve;
	STRUCT_HSV_BOUND *hsv_pastis;

	STRUCT_HSV_BOUND *hsv_Tete[2];
	STRUCT_HSV_BOUND *hsv_T_torso[2];	STRUCT_HSV_BOUND *hsv_B_torso[2];
	STRUCT_HSV_BOUND *hsv_L_shoulder[2];	STRUCT_HSV_BOUND *hsv_R_shoulder[2];
	STRUCT_HSV_BOUND *hsv_L_elbow[2];	STRUCT_HSV_BOUND *hsv_R_elbow[2];
	STRUCT_HSV_BOUND *hsv_L_hand[2];	STRUCT_HSV_BOUND *hsv_R_hand[2];
	STRUCT_HSV_BOUND *hsv_L_knee[2];	STRUCT_HSV_BOUND *hsv_R_knee[2];
	STRUCT_HSV_BOUND *hsv_L_foot[2];	STRUCT_HSV_BOUND *hsv_R_foot[2];

	int posture; // 0 : inconnu | 1 : assis | 2 : debout

	int Evaluer_angle(cv::Point2f pt1, cv::Point2f pt2, cv::Point2f pt3);

	cv::Mat img;
	cv::Point2f Tete, T_torso, B_torso, L_shoulder, R_shoulder, L_elbow, R_elbow, L_hand, R_hand, L_knee, R_knee, L_foot, R_foot;

	Reco reco;
	Blobs *blobs;

	void Couleurs();
	void Membres();
	std::vector <cv::Point2f> Update_blobs(STRUCT_HSV_BOUND *hsv_1, STRUCT_HSV_BOUND *hsv_2);

};

#endif
