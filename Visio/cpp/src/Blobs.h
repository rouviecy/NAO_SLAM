/*
 * @(#)		Blobs.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Classe de séparation des blobs de couleur
 * 	Utilisation :
 * 		- passer une image input RGB via "Set_img"
 *		- envoyer un pointeur vers les paramètres de segmentation via "Definir_limites_separation"
 * 		- filtrer selon ces paramètres via "Separer"
 *		- détecter les blobs via "Trouver_blobs"
 * 		- optionnel : relier tous les blobs entre eux via "Relier"
 * 		- récupérer les informations utiles via les guetters
 */

#ifndef BLOBS
#define BLOBS

#include <mutex>
#include <opencv2/opencv.hpp>
#include "hsv_params.h"

class Blobs{

public:

	Blobs();

	cv::Mat Get_img_sep() const;			// Guetter sur l'image segmentée par HSV
	cv::Mat Get_img_blobs() const;			// Guetter sur l'image des blobs et leurs centres
	std::vector <cv::Moments> Get_mu() const;	// Guetter sur les moments de chaque blob
	std::vector <cv::Point2i> Get_mc() const;	// Guetter sur le centre massique de chaque blob
	std::vector <cv::Rect> Get_rect() const;	// Guetter sur les rectangles englobants des blobs
	std::vector <double> Get_size() const;		// Guetter sur les tailles des blobs

	void Set_img(cv::Mat image);				// Setter d'image à traiter
	void Definir_limites_separation(hsv_params *hsv);	// Récupération des paramètres de segmentation HSV
	void Separer();						// Séparer selon les paramètres
	void Trouver_blobs();					// Convertir les données en liste de blobs
	void Relier();						// Relier les blobs

private:

	std::mutex mut;

	double seuil_taille_blobs;	// taille minimum des blobs
	cv::Mat morpho_kern;		// pour érodation et dilatation
	cv::Scalar rouge, bleu;		// des couleurs ...

	cv::Mat img_brute;		// image input
	cv::Mat img_HSV;		// image dans l'espace HSV
	cv::Mat img_sep;		// image filtrée HSV
	cv::Mat img_blobs;		// image des blobs
	cv::Scalar sep_min;		// limite inférieure de séparation HSV
	cv::Scalar sep_max;		// limite supérieure de séparation HSV
	int nb_dilate, nb_erode;	// nombre de dilatations/érodations à appliquer

	std::vector <std::vector <cv::Point2i> > liste_blobs;	// liste des blobs
	std::vector <cv::Vec4i> hierarchie_blobs;		// hiérarchie de ces blobs
	std::vector <cv::Moments> mu, mu_;			// moments des blobs
	std::vector <cv::Point2i> mc, mc_;			// centres de masse des blobs
	std::vector <cv::Rect> rect, rect_;			// rectangles englobants des blobs
	std::vector <double> taille;				// aires des blobs

};

#endif
