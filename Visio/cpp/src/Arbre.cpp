#include "Arbre.h"

using namespace std;

// Constructeur
Arbre::Arbre(){
		tracking = Tracking(40);
}

// Ajouter des nouvelles cases à la carte en essayant de trouver des liens
void Arbre::Add_cases(std::vector <STRUCT_VIGNETTE> new_liste){
	if(liste.size() == 0){Copy_cells(new_liste); return;}
	for(size_t i = 0; i < new_liste.size(); i++){
		for(size_t j = 0; j < liste.size(); j++){
			tracking.Set_img_prev(new_liste[i].image);
			tracking.Set_img_next(liste[j].image);
			if(tracking.Try_match()){cout << j << "\tlinked to\t" << i << endl;}
		}
	}
}

// Copier les nouvelles cases dans l'arbre
void Arbre::Copy_cells(std::vector <STRUCT_VIGNETTE> new_liste){
	for(size_t i = 0; i < new_liste.size(); i++){
		this->liste.push_back(new_liste[i]);
	}
}
