/*
 * @(#)		Utils.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Outils divers et variés ...
 */

#ifndef UTILS
#define UTILS

#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>

class Utils{

public:

	static char* string_index(const std::string racine, const int index);
	static int Distance_carree(int x1, int y1, int x2, int y2);
	static bool In_img(cv::Point pt, int max_x, int max_y);
	static std::vector <int> Rot2D(int x, int y, int theta);

};

#endif
