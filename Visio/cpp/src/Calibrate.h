/*
 * @(#)		Calibrate.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Classe permettant de calibrer une caméra
 * 	Utilisation :
 * 		- instancier en envoyant les dimensions de l'échiquier à détecter
 * 		- envoyer un certain nombre d'images de la caméra non-calibrée via "Ajouter_img_calib"
 * 		- lancer le calcul de calibration via "Calibrer" en envoyant la taille des imagesà obtenir
 * 		- passer des images non-calibrées en input via "Set_img", puis récupérer les versions calibrées via "Get_img"
 */

#ifndef CALIBRATE
#define CALIBRATE

#include <opencv2/opencv.hpp>

class Calibrate{

public:

	Calibrate(cv::Size dim_chess);

	cv::Mat Get_img();
	void Set_img(cv::Mat img);
	int Ajouter_img_calib(cv::Mat img_input);
	void Calibrer(cv::Size taille);

private:

	int nb_img_calib;
	cv::Size dim_chess;

	std::vector <cv::Point3f> obj;
	std::vector <std::vector <cv::Point3f> > pts_objet;
	std::vector <std::vector <cv::Point2f> > pts_image;
	std::vector <cv::Mat> rvecs, tvecs;

	cv::Mat img, img_calib;
	cv::Mat mat_cam;
	cv::Mat dist_coeffs;

};

#endif
