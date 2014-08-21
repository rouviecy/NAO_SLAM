/*
 * @(#)		Arbre.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Classe contenant l'arbre de la carte fusionnée
 */

#ifndef ARBRE
#define ARBRE

#include <opencv2/opencv.hpp>
#include "struct_vignette.h"

class Arbre{

public:

	Arbre();
	
	void Add_cases(std::vector <STRUCT_VIGNETTE> liste);


private:

};

#endif
