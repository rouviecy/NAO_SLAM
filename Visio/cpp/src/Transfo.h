/*
 * @(#)		Transfo.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Classe de séparation des blobs de couleur
 */

#ifndef TRANSFO
#define TRANSFO

#include <opencv2/opencv.hpp>
#include "Utils.h"
#include "struct_wrap_bound.h"

class Transfo{

public:

	Transfo();

	cv::Mat Get_img_wrap() const;					// Guetter sur l'image transformée par perspective
	std::vector <cv::Point2f> Get_center() const;
	void Set_img(cv::Mat image);					// Setter d'image à traiter
	void Set_pts_redressement(std::vector <cv::Point2f> pts_input);

	void Definir_parametres_transformation(STRUCT_WRAP_BOUND *wrap);
	void Appliquer_wrap(size_t NB, cv::Size taille_sortie = cv::Size(0, 0), cv::Size retrait_bords = cv::Size(0, 0));
	void Appliquer_wrap2();


private:

	int x1, y1, x2, y2, x3, y3, x4, y4;
	bool deja;

	cv::Mat img_brute;
	cv::Mat img_wrap;

	std::vector <cv::Point2f> pts_input;
	std::vector <cv::Point2f> center;

};

#endif
