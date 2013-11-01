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

	cv::Mat Get_img_sep() const;			// Guetter sur l'image segmentée par HSV
	cv::Mat Get_img_blobs() const;			// Guetter sur l'image des blobs et leurs centres
	std::vector <cv::Moments> Get_mu() const;	// Guetter sur les moments de chaque blob
	std::vector <cv::Point2f> Get_mc() const;	// Guetter sur le centre massique de chaque blob
	std::vector <cv::Rect> Get_rect() const;	// Guetter sur les rectangles englobants des blobs

	void Set_img(cv::Mat image);				// Setter d'image à traiter (déjà en HSV)
	void Definir_limites_separation(STRUCT_HSV_BOUND *hsv);	// Récupération des paramètres de segmentation HSV
	void Separer();						// Séparer selon les paramètres
	void Trouver_blobs();					// Convertir les données en liste de blobs

private:

	double seuil_taille_blobs;

	cv::Mat img_brute;
	cv::Mat img_HSV;
	cv::Mat img_sep;
	cv::Mat img_blobs;
	cv::Scalar sep_min;
	cv::Scalar sep_max;
	cv::Scalar rouge, bleu;

	std::vector <std::vector <cv::Point2i> > liste_blobs;
	std::vector <cv::Vec4i> hierarchie_blobs;
	std::vector <cv::Moments> mu, mu_;
	std::vector <cv::Point2f> mc, mc_;
	std::vector <cv::Rect> rect, rect_;

};

#endif
