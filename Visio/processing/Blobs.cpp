#include "Blobs.h"

using namespace std;

// Constructeurs
Blobs::Blobs(){
	Definir_limites_separation(0, 30, 150, 255, 120, 255);
}

// Séparateur de couleurs
void Blobs::Separer(){inRange(img_brute, sep_min, sep_max, img_sep);}

void Blobs::Definir_limites_separation(int H_min, int H_max, int S_min, int S_max, int V_min, int V_max){
	sep_min = cv::Scalar(H_min, S_min, V_min);
	sep_max = cv::Scalar(H_max, S_max, V_max);
}

// Getters et Setters
cv::Mat Blobs::Get_img_sep() const{return img_sep;}
void Blobs::Set_img(cv::Mat image){image.copyTo(img_brute);}
