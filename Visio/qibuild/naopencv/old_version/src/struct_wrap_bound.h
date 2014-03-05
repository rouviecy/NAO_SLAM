/*
 * @(#)		struct_wrap_bound.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Structure représentant les transformations perspective
 */

// On charge ce header qu'une seule fois
#ifndef DEF_WRAP_BOUND
#define DEF_WRAP_BOUND

#include <stdlib.h>
#include <string.h>

typedef struct{
	int x1, y1, x2, y2, x3, y3, x4, y4;
	schar* winname;		// nom fenêtre de la GUI
	// noms trackbar
	schar* name_x1;
	schar* name_y1;
	schar* name_x2;
	schar* name_y2;
	schar* name_x3;
	schar* name_y3;
	schar* name_x4;
	schar* name_y4;
} STRUCT_WRAP_BOUND;

#endif
