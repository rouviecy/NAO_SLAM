/*
 * @(#)		Carte.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Classe contenant une carte de vignettes
 */

#ifndef CARTE
#define CARTE

#include <opencv2/opencv.hpp>
#include "struct_vignette.h"

class Carte{

public:

	Carte();

	void Remplir_buffer(cv::Mat image, std::vector <cv::Point2i> quad);
	void Traiter_buffer();
	void Clear();

private:

	STRUCT_VIGNETTE root;
	bool is_empty;
	std::vector <STRUCT_VIGNETTE> liste;
	std::vector <cv::Mat> buffer_img;
	std::vector <std::vector <cv::Point2i> > buffer_quad;

	STRUCT_VIGNETTE New_vignette(cv::Mat image, std::vector <cv::Point2i> quad);
	void Lier_vignettes(int id_fixe, cv::Mat image, int rotation, int dx, int dy, std::vector <cv::Point2i> quad);

};

#endif
