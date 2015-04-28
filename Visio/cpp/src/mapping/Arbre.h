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
#include "../Tracking.h"
#include "../struct_vignette.h"
#include "../Utils.h"

class Arbre{

public:

	Arbre(bool allow_overwrite = false);

	void Set_overwrite(bool allow_overwrite);
	bool Add_cases(std::vector <STRUCT_VIGNETTE> new_liste);
	cv::Mat Print(bool numeros);
	std::vector <STRUCT_VIGNETTE> get_liste() const;


private:

	std::vector <STRUCT_VIGNETTE> liste, candidats;

	Tracking tracking;

	bool allow_overwrite;

	void Overwrite_management();
	void Copy_cells(std::vector <STRUCT_VIGNETTE> new_liste);

};

#endif
