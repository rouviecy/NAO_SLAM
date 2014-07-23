#include "Carte.h"

using namespace std;

// Constructeur
Carte::Carte(){
	Clear();
}

void Carte::Remplir_buffer(cv::Mat image, vector <cv::Point2f> quadrillage){

}

void Carte::Traiter_buffer(){

}

void Carte::Clear(){
	liste.clear();
	buffer_img.clear();
	buffer_quad.clear();
	is_empty = true;
}
