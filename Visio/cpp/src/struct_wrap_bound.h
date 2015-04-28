/*
 * @(#)		struct_wrap_bound.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Structure représentant les transformations perspective
 */

#ifndef DEF_WRAP_BOUND
#define DEF_WRAP_BOUND

#include <stdlib.h>
#include <string.h>

typedef struct{
	int x1, y1, x2, y2, x3, y3, x4, y4;
	char winname[128];
	char name_x1[128];
	char name_y1[128];
	char name_x2[128];
	char name_y2[128];
	char name_x3[128];
	char name_y3[128];
	char name_x4[128];
	char name_y4[128];
} STRUCT_WRAP_BOUND;

#endif
