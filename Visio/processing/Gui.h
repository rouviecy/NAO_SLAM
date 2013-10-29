/*
 * @(#)		Gui.h
 * @version	1.2
 * @autor	C. Rouvière
 */

/**
 * Classe affichant une image OpenCV2 dans une fenêtre
 *	- peut également y ajouter des vecteurs
 */

#ifndef GUI
#define GUI

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdlib.h>
#include <string.h>
#include "struct_HSV_bound.h"

class Gui{

public:

	Gui();
	~Gui();

	void Creer_trackbar_HSV_sep(const char* titre_fenetre);
	STRUCT_HSV_BOUND *Get_HSV_bound() const;

	void Afficher_image(const std::string titre_fenetre, cv::Mat image);
	void Pad(const std::string titre_fenetre, const float dx, const float dy, const float dx_max, const float dy_max);
	void Ajouter_vecteurs(
		const std::string titre_fenetre,	// titre de la fenêtre
		cv::Mat image,				// image à traiter
		std::vector<cv::Point2f> pts_prev,	// tableau des points initiaux
		std::vector<cv::Point2f> pts_next);	// tableau des points finals

private:

	#define TAILLE_POD 200

	STRUCT_HSV_BOUND *hsv;

	cv::Scalar rouge;
	cv::Size dim_1;
	cv::Point pod_centre;

	static void Callback_HSV(int value, void *userdata);

};

#endif
