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

typedef struct{
	int H_min;
	int H_max;
	int S_min;
	int S_max;
	int V_min;
	int V_max;
} STRUCT_HSV_BOUND;

#endif
