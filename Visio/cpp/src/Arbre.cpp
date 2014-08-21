#include "Arbre.h"

using namespace std;

// Constructeur
Arbre::Arbre(){
		tracking = Tracking(40);
}

// Ajouter des nouvelles cases à la carte en essayant de trouver des liens
void Arbre::Add_cases(std::vector <STRUCT_VIGNETTE> new_liste){
	if(liste.size() == 0){Copy_cells(new_liste); return;}
	int delta_x = 0, delta_y = 0, delta_theta = 0;
	bool found = false;
	for(size_t i = 0; i < new_liste.size() && !found; i++){
		tracking.Set_img_prev(new_liste[i].image);
		for(size_t j = 0; j < liste.size(); j++){
			tracking.Set_img_next(liste[j].image);
			if(tracking.Try_match(20, 15)){
				delta_x = new_liste[i].x - liste[j].x;
				delta_y = new_liste[i].y - liste[j].y;
				delta_theta = - tracking.Get_orientation();
				found = true;
				break;
			}
		}
	}
	if(!found){return;}
	switch(delta_theta){
		case 0:
			for(size_t i = 0; i < new_liste.size(); i++){
				STRUCT_VIGNETTE nouveau = new_liste[i];
				nouveau.x -= delta_x;
				nouveau.y -= delta_y;
				liste.push_back(nouveau);
			}
			break;
		case 1:
			for(size_t i = 0; i < new_liste.size(); i++){
				STRUCT_VIGNETTE nouveau = new_liste[i];
				nouveau.x += delta_y;
				nouveau.y -= delta_x;
				liste.push_back(nouveau);
			}
			break;
		case 2:
			for(size_t i = 0; i < new_liste.size(); i++){
				STRUCT_VIGNETTE nouveau = new_liste[i];
				nouveau.x += delta_x;
				nouveau.y += delta_y;
				liste.push_back(nouveau);
			}
			break;
		case 3:
			for(size_t i = 0; i < new_liste.size(); i++){
				STRUCT_VIGNETTE nouveau = new_liste[i];
				nouveau.x -= delta_y;
				nouveau.y += delta_x;
				liste.push_back(nouveau);
			}
			break;
	}
}

// Copier les nouvelles cases dans l'arbre
void Arbre::Copy_cells(std::vector <STRUCT_VIGNETTE> new_liste){
	for(size_t i = 0; i < new_liste.size(); i++){
		this->liste.push_back(new_liste[i]);
	}
}

cv::Mat Arbre::Print(bool numeros){
cout << liste.size() << endl;
	if(liste.size() == 0){return cv::Mat();}
	int min_x = 0, max_x = 0, min_y = 0, max_y = 0;
	int vignette_w = liste[0].image.size().width;
	int vignette_h = liste[0].image.size().height;
	for(size_t i = 0; i < liste.size(); i++){
		if(liste[i].x < min_x){min_x = liste[i].x;}
		if(liste[i].x > max_x){max_x = liste[i].x;}
		if(liste[i].y < min_y){min_y = liste[i].y;}
		if(liste[i].y > max_y){max_y = liste[i].y;}
	}
	int map_w = vignette_w * (max_x - min_x + 1);
	int map_h = vignette_h * (max_y - min_y + 1);
	cv::Mat map(cv::Size(map_w, map_h), liste[0].image.type(), cv::Scalar(0, 0, 0));
	for(size_t i = 0; i < liste.size(); i++){
		cv::Size taille = liste[i].image.size();
		cv::Mat vignette_rot;
		cv::Mat mat_rot = cv::getRotationMatrix2D(cv::Point2i(taille.width / 2, taille.height / 2), - liste[i].orientation * 90, 1);
		cv::warpAffine(liste[i].image, vignette_rot, mat_rot, taille);
		int pos_x = vignette_w * (liste[i].x - min_x);
		int pos_y = vignette_h * (liste[i].y - min_y);
		cv::Rect roi(cv::Point(pos_x, pos_y), taille);
		cv::Mat destinationROI = map(roi);
		vignette_rot.copyTo(destinationROI);
		if(numeros){cv::putText(destinationROI, to_string(i), cv::Point2i(vignette_w / 2, vignette_h / 2), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);}

	}
	return map;
}
