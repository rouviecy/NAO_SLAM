#include "Blobs.h"

using namespace std;

// Constructeur - Destructeur
Blobs::Blobs(){
	STRUCT_HSV_BOUND *hsv = (STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	hsv->H_min = 0;
	hsv->H_max = 30;
	hsv->S_min = 150;
	hsv->S_max = 255;
	hsv->V_min = 120;
	hsv->V_max = 255;
	Definir_limites_separation(hsv);
	free(hsv);
}

Blobs::~Blobs(){

}

// Séparateur de couleurs
void Blobs::Separer(){inRange(img_brute, sep_min, sep_max, img_sep);}

void Blobs::Definir_limites_separation(STRUCT_HSV_BOUND *hsv){
	sep_min = cv::Scalar(hsv->H_min, hsv->S_min, hsv->V_min);
	sep_max = cv::Scalar(hsv->H_max, hsv->S_max, hsv->V_max);
}

// Getters et Setters
cv::Mat Blobs::Get_img_sep() const{return img_sep;}
void Blobs::Set_img(cv::Mat image){image.copyTo(img_brute);}
