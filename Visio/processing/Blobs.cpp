#include "Blobs.h"

using namespace std;

// Constructeur
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

// Séparateur de couleurs
void Blobs::Separer(){inRange(img_brute, sep_min, sep_max, img_sep);}

// Mise à jour des paramètres de segmentation HSV
void Blobs::Definir_limites_separation(STRUCT_HSV_BOUND *hsv){
	sep_min = cv::Scalar(hsv->H_min, hsv->S_min, hsv->V_min);
	sep_max = cv::Scalar(hsv->H_max, hsv->S_max, hsv->V_max);
}

// Séparer les blobs
void Blobs::Trouver_blobs(){
	img_blobs = cv::Mat(img_sep.size(), CV_8UC3, cv::Scalar(0, 0, 0));
	cv::findContours(img_sep, liste_blobs, hierarchie_blobs, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	if(hierarchie_blobs.size() <= 0){return;}
	for(int index = 0; index >= 0; index = hierarchie_blobs[index][0]){
		cv::Scalar couleur(rand()&255, rand()&255, rand()&255);
		drawContours(img_blobs, liste_blobs, index, couleur, CV_FILLED, 8, hierarchie_blobs);
	}
	// TODO : Nettoyer cette partie du code
	std::vector<cv::Moments> mu(liste_blobs.size());
	std::vector<cv::Point2f> mc(liste_blobs.size());
	cv::Mat drawing = cv::Mat::zeros(img_sep.size(), CV_8UC3);
	for(size_t i = 0; i < liste_blobs.size(); i++){
		mu[i] = cv::moments(liste_blobs[i], false);
		mc[i] = cv::Point2f(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00);
		cv::circle(drawing, mc[i], 4, cv::Scalar(255, 0, 0), -1, 8, 0 );
	}
	cv::imshow("Contours", drawing);
}

// Getters et Setters
cv::Mat Blobs::Get_img_sep() const{return img_sep;}
cv::Mat Blobs::Get_img_blobs() const{return img_blobs;}
void Blobs::Set_img(cv::Mat image){image.copyTo(img_brute);}
