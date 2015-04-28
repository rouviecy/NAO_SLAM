#include "Multimap.h"

using namespace std;

Multimap::Multimap(){
	liste_maps.clear();
	nb_windows = 0;
}

void Multimap::Create_map(vector <STRUCT_VIGNETTE> input){
	Arbre arbre(true);
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

void Multimap::Try_fusion(){
	vector <Arbre> ::iterator it1, it2;
	for(it1 = liste_maps.begin(); it1 != liste_maps.end(); it1++){
		bool ajout_actif = false;
		for(it2 = it1 + 1; it2 != liste_maps.end(); it2++){
			if(it1->Add_cases(it2->get_liste())){
				liste_maps.erase(it2); it2--;
				ajout_actif = true;
				break;
			}
		}
	}
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
	int nouv_nb_windows = nb_windows;
	for(int i = liste_maps.size(); i < nb_windows; i++){
		string name = "map" + to_string(i);
		cv::destroyWindow(name);
		nouv_nb_windows--;
	}
	nb_windows = nouv_nb_windows;
}
