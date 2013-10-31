/*
 * @(#)		Blobs.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Classe de séparation des blobs de couleur
 */

#ifndef BLOBS
#define BLOBS

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "struct_HSV_bound.h"

class Blobs{

public:

	Blobs();

	cv::Mat Get_img_sep() const;
	cv::Mat Get_img_blobs() const;
	cv::Mat Get_img_centers() const;
	void Set_img(cv::Mat image);
	void Definir_limites_separation(STRUCT_HSV_BOUND *hsv);
	void Separer();
	void Trouver_blobs();

private:

	cv::Mat img_brute;
	cv::Mat img_sep;
	cv::Mat img_blobs;
	cv::Mat img_centers;
	cv::Scalar sep_min;
	cv::Scalar sep_max;
	cv::Scalar rouge;

	std::vector <std::vector <cv::Point2i> > liste_blobs;
	std::vector <cv::Vec4i> hierarchie_blobs;

};

#endif
