/*
 * @(#)		struct_HSV_bound.h
 * @version	2.0
 * @autor	C. Rouvière
 */

/**
 * Structure représentant des limites de filtrage HSV
 */

// On charge ce header qu'une seule fois
#ifndef DEF_HSV_BOUND
#define DEF_HSV_BOUND

#include <stdlib.h>
#include <string.h>

typedef struct{
	int H_min;		// seuil minimum de chrominance
	int H_max;		// seuil maximum de chrominance
	int S_min;		// seuil minimum de saturation
	int S_max;		// seuil maximum de saturation
	int V_min;		// seuil minimum de luminance
	int V_max;		// seuil maximum de luminance
	int seuil;		// seuil minimum de taille de blob
	int nb_dilate;		// nombre de dilatations à appliquer
	int nb_erode;		// nombre d'érosions à appliquer
	schar* winname;		// nom fenêtre de la GUI
	// noms trackbar
	schar* name_H_min;
	schar* name_H_max;
	schar* name_S_min;
	schar* name_S_max;
	schar* name_V_min;
	schar* name_V_max;
	schar* name_seuil;
	schar* name_nb_dilate;
	schar* name_nb_erode;
} STRUCT_HSV_BOUND;

#endif
