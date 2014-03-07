/*
 * @(#)		Gui.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Classe affichant une image OpenCV2 dans une fenêtre
 *	- peut également y ajouter des vecteurs
 * ATTENTION : INCOMPATIBLE NAO !
 */

#ifndef GUI
#define GUI

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include "struct_HSV_bound.h"
#include "struct_wrap_bound.h"

class Gui{

public:

	Gui(); ~Gui();

	void Creer_trackbar_HSV_sep(const char* titre_fenetre);				// initialisation de la fenêtre des trackbars de séparation HSV
	void Creer_trackbar_HSV_sep2(const char* titre_fenetre);			// initialisation de la fenêtre des trackbars de séparation HSV
	void Creer_trackbar_transfo(const char* titre_fenetre);				// initialisation de la fenêtre des trackbars de transformation
	STRUCT_HSV_BOUND *Get_HSV_bound() const;					// pointeur vers la structure contenant les paramètres de séparation
	STRUCT_HSV_BOUND *Get_HSV_bound2() const;					// pointeur vers la structure contenant les paramètres de séparation 2
	STRUCT_WRAP_BOUND *Get_wrap_bound() const;					// pointeur vers la structure contenant les paramètres de transformation
	void Controler_souris(std::vector <cv::Point2f> mc, int width, int height);	// contrôler la souris en fonction de la position du 1er blob
	void Cliquer(std::vector <cv::Point2f> mc);					// cliquer si le vecteur n'est pas vide
	void Afficher_image(const std::string titre_fenetre, const cv::Mat image);
	void Pad(const std::string titre_fenetre, const float dx, const float dy, const float dx_max, const float dy_max);
	void Ajouter_vecteurs(
		const std::string titre_fenetre,	// titre de la fenêtre
		const cv::Mat image,			// image à traiter
		std::vector<cv::Point2f> pts_prev,	// tableau des points initiaux
		std::vector<cv::Point2f> pts_next);	// tableau des points finals

private:

	#define TAILLE_POD 200

	STRUCT_HSV_BOUND *hsv;
	STRUCT_HSV_BOUND *hsv2;
	STRUCT_WRAP_BOUND *wrap;

	cv::Scalar rouge;
	cv::Size dim_1;
	cv::Point pod_centre;

	Display *dpy;
	Window root_window;
	unsigned char buttonMap[3];
	int buttonCount;

	static void Callback_HSV(int value, void *userdata);
	static void Callback_wrap(int value, void *object);

};

#endif
