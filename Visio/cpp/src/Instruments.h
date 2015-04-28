/*
 * @(#)		Instruments.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Classe d'instrumentation des images OpenCV
 * 	- Histogrammes
 */

#ifndef INSTRUMENTS
#define INSTRUMENTS

#include <opencv2/opencv.hpp>

class Instruments{

public:

	Instruments(int hist_width, int hist_height);

	void Set_img(cv::Mat image);
	cv::Mat Get_hist_H();
	void Calculer_hist_H(int nb_elems);

private:

	cv::Mat img_degrade;
	cv::Mat img_brute;
	cv::Mat hist_H, img_hist_H;
	int hist_width, hist_height;
	void Colorier();
	cv::Scalar noir;

};

#endif
