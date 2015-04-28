/*
 * @(#)		struct_nom.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Structure contenant une image et son nom
 */

// On charge ce header qu'une seule fois
#ifndef DEF_STRUCT_NOM
#define DEF_STRUCT_NOM

#include <string>

typedef struct{
	std::string nom;
	std::string nom_complet;
	std::string extension;
} STRUCT_NOM;

#endif
