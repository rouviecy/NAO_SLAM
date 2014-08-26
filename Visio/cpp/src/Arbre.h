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
#include "Tracking.h"
#include "struct_vignette.h"
#include "Utils.h"

class Arbre{

public:

	Arbre();
	
	void Add_cases(std::vector <STRUCT_VIGNETTE> new_liste);
	cv::Mat Print(bool numeros);


private:

	std::vector <STRUCT_VIGNETTE> liste;
	
	Tracking tracking;
	
	void Copy_cells(std::vector <STRUCT_VIGNETTE> new_liste);

};

#endif
