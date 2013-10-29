/*
 * @(#)		struct_HSV_bound.h
 * @version	1.0
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
	int H_min;
	int H_max;
	int S_min;
	int S_max;
	int V_min;
	int V_max;
	schar* name_H_min;
	schar* name_H_max;
	schar* name_S_min;
	schar* name_S_max;
	schar* name_V_min;
	schar* name_V_max;
	schar* winname;
} STRUCT_HSV_BOUND;

#endif
