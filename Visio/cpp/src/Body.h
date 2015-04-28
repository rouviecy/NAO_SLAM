/*
 * @(#)		Body.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Classe de reconstruction de corps
 * 	Utilisation :
 * 		- passer l'image input via "Set_img"
 * 		- détecter les membres voulus via les "Detecter_*"
 * 		- récupérer les coordonnées des membres via les guetters
 */

#ifndef BODY
#define BODY

#include <opencv2/opencv.hpp>
#include "Blobs.h"
#include "Reco.h"
#include "hsv_params.h"

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
	void Set_img(cv::Mat img);
	cv::Point2i Get_Head();
	cv::Point2i Get_T_torso();	cv::Point2i Get_B_torso();
	cv::Point2i Get_L_shoulder();	cv::Point2i Get_R_shoulder();
	cv::Point2i Get_L_elbow();	cv::Point2i Get_R_elbow();
	cv::Point2i Get_L_hand();	cv::Point2i Get_R_hand();
	cv::Point2i Get_L_knee();	cv::Point2i Get_R_knee();
	cv::Point2i Get_L_foot();	cv::Point2i Get_R_foot();

private:

	hsv_params *hsv_jaune;
	hsv_params *hsv_vert;
	hsv_params *hsv_rose;
	hsv_params *hsv_lavande;
	hsv_params *hsv_turq;
	hsv_params *hsv_beige;
	hsv_params *hsv_mauve;
	hsv_params *hsv_pastis;

	hsv_params *hsv_Tete[2];
	hsv_params *hsv_T_torso[2];	hsv_params *hsv_B_torso[2];
	hsv_params *hsv_L_shoulder[2];	hsv_params *hsv_R_shoulder[2];
	hsv_params *hsv_L_elbow[2];	hsv_params *hsv_R_elbow[2];
	hsv_params *hsv_L_hand[2];	hsv_params *hsv_R_hand[2];
	hsv_params *hsv_L_knee[2];	hsv_params *hsv_R_knee[2];
	hsv_params *hsv_L_foot[2];	hsv_params *hsv_R_foot[2];

	cv::Mat img;
	cv::Point2i Tete, T_torso, B_torso, L_shoulder, R_shoulder, L_elbow, R_elbow, L_hand, R_hand, L_knee, R_knee, L_foot, R_foot;

	Reco reco;
	Blobs *blobs;

	void Couleurs();
	void Membres();
	std::vector <cv::Point2i> Update_blobs(hsv_params *hsv_1, hsv_params *hsv_2);

};

#endif
