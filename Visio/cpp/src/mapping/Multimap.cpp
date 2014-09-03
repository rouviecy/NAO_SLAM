#include "Multimap.h"

using namespace std;

Multimap::Multimap(){
	liste_maps.clear();
	nb_windows = 0;
}

void Multimap::Create_map(vector <STRUCT_VIGNETTE> input){
	Arbre arbre(false);
	arbre.Add_cases(input);
	liste_maps.push_back(arbre);
}

void Multimap::Add_map(vector <STRUCT_VIGNETTE> input){
	if(liste_maps.size() == 0){Create_map(input); return;}
	bool ajout_actif = false;
	for(size_t i = 0; i < liste_maps.size(); i++){
		if(liste_maps[i].Add_cases(input)){
			ajout_actif = true;
			break;
		}
	}
	if(!ajout_actif){Create_map(input);}
}

void Multimap::Show_maps(){
	for(int i = 0; i < liste_maps.size(); i++){
		string name = "map" + to_string(i);
		if(i >= nb_windows){
			cv::namedWindow(name, cv::WINDOW_NORMAL);
			nb_windows++;
		}
		cv::imshow(name, liste_maps[i].Print(true));
	}
}
