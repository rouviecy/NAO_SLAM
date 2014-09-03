#include "Multimap.h"

using namespace std;

Multimap::Multimap(){
	liste_maps.clear();
}

void Multimap::Create_map(vector <STRUCT_VIGNETTE> input){
	Arbre arbre(false);
	arbre.Add_cases(input);
	liste_maps.push_back(arbre);
	cv::imshow("map", liste_maps[0].Print(true));
}

void Multimap::Add_map(vector <STRUCT_VIGNETTE> input){
	if(liste_maps.size() == 0){Create_map(input); return;}

	liste_maps[0].Add_cases(input);
	cv::imshow("map", liste_maps[0].Print(true));
}
