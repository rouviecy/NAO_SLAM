/*
 * @(#)		Transfo.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Classe de séparation des blobs de couleur
 */

#ifndef TRANSFO
#define TRANSFO

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "Utils.h"
#include "struct_wrap_bound.h"

class Transfo{

public:

	Transfo();

	cv::Mat Get_img_wrap() const;			// Guetter sur l'image transformée par perspective
	std::vector <cv::Point2f> Get_center() const;
	void Set_img(cv::Mat image);			// Setter d'image à traiter
	void Set_pts_redressement(std::vector <cv::Point2f> pts_input);

	void Definir_parametres_transformation(STRUCT_WRAP_BOUND *wrap);
	void Appliquer_wrap();				// Appliquer une transformation perspective


private:

	int x1, y1, x2, y2, x3, y3, x4, y4;
	bool deja;

	cv::Mat img_brute;
	cv::Mat img_wrap;

	std::vector <cv::Point2f> pts_input;
	std::vector <cv::Point2f> center;

};

#endif
