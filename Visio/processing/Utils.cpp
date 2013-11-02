#include "Utils.h"

using namespace std;

// Concaténer une chaîne de caractère avec un integer pour obtenir un char*
char* Utils::string_index(const std::string racine, const int index){
	std::stringstream ss;
	ss << racine << index;
	return (char*) ss.str().c_str();
}
