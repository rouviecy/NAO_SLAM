/*
 * @(#)		Multimap.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Classe contenant tous les arbres
 */

#ifndef MULTIMAP
#define MULTIMAP

#include <opencv2/opencv.hpp>
#include "Arbre.h"
#include "../struct_vignette.h"

class Multimap{

public:

	Multimap();
	
	void Add_map(std::vector <STRUCT_VIGNETTE> input);
	void Try_fusion();
	void Show_maps();


private:

	std::vector <Arbre> liste_maps;
	int nb_windows;
	
	void Create_map(std::vector <STRUCT_VIGNETTE> input);

};

#endif
