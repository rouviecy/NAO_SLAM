/*
 * @(#)		Blobs.h
 * @version	1.0
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
	~Blobs();

	cv::Mat Get_img_sep() const;
	void Set_img(cv::Mat image);
	void Definir_limites_separation(STRUCT_HSV_BOUND *hsv);
	void Separer();

private:

	cv::Mat img_brute;
	cv::Mat img_sep;
	cv::Scalar sep_min;
	cv::Scalar sep_max;

};

#endif
