#include "Utils.h"

using namespace std;

// Concaténer une chaîne de caractère avec un integer pour obtenir un char*
char* Utils::string_index(const std::string racine, const int index){
	stringstream ss;
	ss << racine << index;
	return (char*) ss.str().c_str();
}

// Calculer une distance au carré pour la norme 2
int Utils::Distance_carree(int x1, int y1, int x2, int y2){
	int dx = x2 - x1, dy = y2 - y1;
	return dx*dx + dy*dy;
}
