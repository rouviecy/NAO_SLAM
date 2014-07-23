#include "Carte.h"

using namespace std;

// Constructeur
Carte::Carte(){
	Clear();
}

void Carte::Remplir_buffer(cv::Mat image, vector <cv::Point2i> quad){
	buffer_img.push_back(image);
	buffer_quad.push_back(quad);
}

void Carte::Traiter_buffer(){
	if(is_empty){
		root = New_vignette(buffer_img.back(), buffer_quad.back());
		buffer_img.pop_back();
		buffer_quad.pop_back();
	}
	while(!buffer_img.empty()){
		for(int i = 0; i < buffer_img.size(); i++){
			cv::Point2i Ai = buffer_quad[i][0];
			cv::Point2i Bi = buffer_quad[i][1];
			cv::Point2i Ci = buffer_quad[i][2];
			cv::Point2i Di = buffer_quad[i][3];
			for(int j = 0; j < liste.size(); j++){
				cv::Point2i Aj = liste[j].A;
				cv::Point2i Bj = liste[j].B;
				cv::Point2i Cj = liste[j].C;
				cv::Point2i Dj = liste[j].D;
			}
		}
	}
}

void Carte::Clear(){
	liste.clear();
	buffer_img.clear();
	buffer_quad.clear();
	is_empty = true;
}

STRUCT_VIGNETTE Carte::New_vignette(cv::Mat image, vector <cv::Point2i> quad){
	STRUCT_VIGNETTE vignette;
	vignette.image =	image;
	vignette.index =	liste.size();
	vignette.x =		0;
	vignette.y =		0;
	vignette.orientation =	0;
	vignette.ouest =	-1;
	vignette.est =		-1;
	vignette.nord =		-1;
	vignette.sud =		-1;
	vignette.A =		quad[0];
	vignette.B =		quad[1];
	vignette.C =		quad[2];
	vignette.D =		quad[3];
	return vignette;
}
