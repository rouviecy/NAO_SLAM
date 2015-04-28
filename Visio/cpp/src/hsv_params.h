/*
 * @(#)		hsv_params.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Structure de paramètres HSV
 */

#ifndef HSV_PARAMS
#define HSV_PARAMS

//#include "../TCP_client.h"

typedef struct{
	int H_min, S_min, V_min;
	int H_max, S_max, V_max;
	int nb_dilate, nb_erode;
	int seuil;
//	TCP_client* tcp;
	char winname[128];
	char name_H_min[128], name_S_min[128], name_V_min[128];
	char name_H_max[128], name_S_max[128], name_V_max[128];
	char name_nb_dilate[128], name_nb_erode[128];
	char name_seuil[128];
} hsv_params;

#endif
