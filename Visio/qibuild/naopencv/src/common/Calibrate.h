/*
 * @(#)		Calibrate.h
 * @version	2.0
 * @autor	C. Rouvière
 */

/**
 * Classe permettant de calibrer une caméra
 */

#ifndef CALIBRATE
#define CALIBRATE

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>

class Calibrate{

public:

	Calibrate(const cv::Size dim_chess);

	cv::Mat Get_img();
	void Set_img(const cv::Mat img);
	int Ajouter_img_calib(cv::Mat img_input);
	void Calibrer(const cv::Size taille);

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
