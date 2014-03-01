/*
 * @(#)		Utils.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Outils divers et variés ...
 */

#ifndef UTILS
#define UTILS

#include <string>
#include <sstream>

class Utils{

public:

	static char* string_index(const std::string racine, const int index);
	static int Distance_carree(int x1, int y1, int x2, int y2);

};

#endif
