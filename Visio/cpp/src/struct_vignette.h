/*
 * @(#)		struct_vignette.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Structure contenant une image, un numéro d'index, des coordonnées, une orientation et des liens vers ses voisins
 */

// On charge ce header qu'une seule fois
#ifndef DEF_STRUCT_VIGNETTE
#define DEF_STRUCT_VIGNETTE

#include <string>
#include <opencv2/opencv.hpp>

typedef struct{
	cv::Mat image;		// image contenue dans la vignette
	int index;		// nid
	int x;			// abscisse
	int y;			// ordonnée
	int orientation;	// orientation dans le sens trigonométrique (0 : 0° | 1 : 90° | 2 : 180° | 3 : 270°)
	int ouest;		// nid du voisin à l'Ouest
	int est;		// nid du voisin à l'Est
	int nord;		// nid du voisin au Nord
	int sud;		// nid du voisin au Sud
	cv::Point2f A;		// coin Nord-Ouest
	cv::Point2f B;		// coin Nord-Est
	cv::Point2f C;		// coin Sud-Est
	cv::Point2f D;		// coin Sud-Ouest
} STRUCT_VIGNETTE;

#endif
