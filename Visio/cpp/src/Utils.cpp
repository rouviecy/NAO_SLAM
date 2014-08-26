#include "Utils.h"

using namespace std;

// Concaténer une chaîne de caractère avec un integer pour obtenir un char*
char* Utils::string_index(const std::string racine, const int index){
	std::stringstream ss;
	ss << racine << index;
	return (char*) ss.str().c_str();
}

// Calculer une distance au carré pour la norme 2
int Utils::Distance_carree(int x1, int y1, int x2, int y2){
	int dx = x2 - x1, dy = y2 - y1;
	return dx*dx + dy*dy;
}

// Test si le point est dans l'image
bool Utils::In_img(cv::Point pt, int max_x, int max_y){
	return pt.x > 0 && pt.x < max_x && pt.y > 0 && pt.y < max_y;
}

// Effectue une rotation 2D
vector <int> Utils::Rot2D(int x, int y, int theta){
	vector <int> resultat(2);
	switch(theta){
		case 0:	resultat[0] = +x; resultat[1] = +y; break;
		case 1:	resultat[0] = -y; resultat[1] = +x; break;
		case 2:	resultat[0] = -x; resultat[1] = -y; break;
		case 3:	resultat[0] = +y; resultat[1] = -x; break;
	}
	return resultat;
}
