/*
 * @(#)		Blobs.h
 * @version	2.0
 * @autor	C. Rouvière
 */

/**
 * Classe de séparation des blobs de couleur
 */

#ifndef BLOBS
#define BLOBS

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "struct_HSV_bound.h"

class Blobs{

public:

	Blobs();

	cv::Mat Get_img_sep() const;			// Guetter sur l'image segmentée par HSV
	cv::Mat Get_img_blobs() const;			// Guetter sur l'image des blobs et leurs centres
	std::vector <cv::Moments> Get_mu() const;	// Guetter sur les moments de chaque blob
	std::vector <cv::Point2f> Get_mc() const;	// Guetter sur le centre massique de chaque blob
	std::vector <cv::Rect> Get_rect() const;	// Guetter sur les rectangles englobants des blobs

	void Set_img(cv::Mat image);				// Setter d'image à traiter
	void Definir_limites_separation(STRUCT_HSV_BOUND *hsv);	// Récupération des paramètres de segmentation HSV
	void Separer();						// Séparer selon les paramètres
	void Trouver_blobs();					// Convertir les données en liste de blobs
	void Relier();						// Relier les blobs

private:

	double seuil_taille_blobs;
	cv::Mat morpho_kern;

	cv::Mat img_brute;
	cv::Mat img_HSV;
	cv::Mat img_sep;
	cv::Mat img_blobs;
	cv::Scalar sep_min;
	cv::Scalar sep_max;
	int nb_dilate, nb_erode;
	cv::Scalar rouge, bleu;

	std::vector <std::vector <cv::Point2i> > liste_blobs;
	std::vector <cv::Vec4i> hierarchie_blobs;
	std::vector <cv::Moments> mu, mu_;
	std::vector <cv::Point2f> mc, mc_;
	std::vector <cv::Rect> rect, rect_;

	void Init(const int lissage);

};

#endif
