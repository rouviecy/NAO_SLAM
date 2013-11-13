/*
 * @(#)		Calibrate.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Classe permettant de calibrer une caméra
 */

#ifndef CALIBRATE
#define CALIBRATE

#include <opencv/cv.h>
#include <opencv/highgui.h>

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
