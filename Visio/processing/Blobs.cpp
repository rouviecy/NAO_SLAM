#include "Blobs.h"

using namespace std;

// Constructeur
Blobs::Blobs(){
	rouge = cv::Scalar(0, 0, 255);
	seuil_taille_blobs = 42;
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

// Séparateur de couleurs
void Blobs::Separer(){inRange(img_brute, sep_min, sep_max, img_sep);}

// Mise à jour des paramètres de segmentation HSV
void Blobs::Definir_limites_separation(STRUCT_HSV_BOUND *hsv){
	sep_min = cv::Scalar(hsv->H_min, hsv->S_min, hsv->V_min);
	sep_max = cv::Scalar(hsv->H_max, hsv->S_max, hsv->V_max);
	seuil_taille_blobs = hsv->seuil;
}

// Séparer les blobs
void Blobs::Trouver_blobs(){
	img_blobs = cv::Mat::zeros(img_sep.size(), CV_8UC3);
	img_centers = cv::Mat::zeros(img_sep.size(), CV_8UC3);
	cv::findContours(img_sep, liste_blobs, hierarchie_blobs, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	if(hierarchie_blobs.size() <= 0){return;}
	std::vector<cv::Moments> mu(liste_blobs.size());
	std::vector<cv::Point2f> mc(liste_blobs.size());
	for(size_t i = 0; i < liste_blobs.size(); i++){
		double aire = cv::contourArea(liste_blobs[i], false);
		if(aire < seuil_taille_blobs){continue;}
		cv::Scalar couleur(rand()&255, rand()&255, rand()&255);
		drawContours(img_blobs, liste_blobs, i, couleur, CV_FILLED, 8, hierarchie_blobs);
		mu[i] = cv::moments(liste_blobs[i], false);
		mc[i] = cv::Point2f(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00);
		cv::circle(img_centers, mc[i], 4, rouge, -1, 8, 0);
	}
}

// Getters et Setters
cv::Mat Blobs::Get_img_sep() const{return img_sep;}
cv::Mat Blobs::Get_img_blobs() const{return img_blobs;}
cv::Mat Blobs::Get_img_centers() const{return img_centers;}
void Blobs::Set_img(cv::Mat image){image.copyTo(img_brute);}
void Blobs::Set_seuil_taille_blobs(double seuil){this->seuil_taille_blobs = seuil;}
