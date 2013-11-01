#include "Blobs.h"

using namespace std;

// Constructeur
Blobs::Blobs(){
	rouge = cv::Scalar(0, 0, 255); bleu = cv::Scalar(255, 0, 0);
	seuil_taille_blobs = 42;
	STRUCT_HSV_BOUND *hsv = (STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	hsv->H_min = 0;
	hsv->H_max = 42;
	hsv->S_min = 150;
	hsv->S_max = 255;
	hsv->V_min = 120;
	hsv->V_max = 255;
	Definir_limites_separation(hsv);
	free(hsv);
}

// Séparateur de couleurs
void Blobs::Separer(){
	inRange(img_HSV, sep_min, sep_max, img_sep);
	blur(img_sep, img_sep, cv::Size(5, 5), cv::Point(-1, -1), cv::BORDER_DEFAULT);
}

// Mise à jour des paramètres de segmentation HSV
void Blobs::Definir_limites_separation(STRUCT_HSV_BOUND *hsv){
	sep_min = cv::Scalar(hsv->H_min, hsv->S_min, hsv->V_min);
	sep_max = cv::Scalar(hsv->H_max, hsv->S_max, hsv->V_max);
	seuil_taille_blobs = hsv->seuil;
}

// Séparer les blobs
void Blobs::Trouver_blobs(){
	img_blobs = cv::Mat::zeros(img_sep.size(), CV_8UC3);
	cv::findContours(img_sep, liste_blobs, hierarchie_blobs, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	if(hierarchie_blobs.size() <= 0){return;}
	mu_.clear(); mc_.clear(); rect_.clear();
	mu.clear(); mc.clear(); rect.clear();
	for(size_t i = 0; i < liste_blobs.size(); i++){
		mu_.push_back(cv::moments(liste_blobs[i], false));
		mc_.push_back(cv::Point2f(mu_[i].m10/mu_[i].m00, mu_[i].m01/mu_[i].m00));
		rect_.push_back(cv::boundingRect(liste_blobs[i]));
		double aire = cv::contourArea(liste_blobs[i], false);
		if(aire < seuil_taille_blobs){continue;}
		mu.push_back(mu_[i]);
		mc.push_back(mc_[i]);
		rect.push_back(rect_[i]);
		drawContours(img_blobs, liste_blobs, i, bleu, CV_FILLED, 8, hierarchie_blobs);
		cv::circle(img_blobs, mc_[i], 4, rouge, -1, 8, 0);
		cv::rectangle(img_blobs, rect_[i], rouge);
	}
}

// Getters et Setters
cv::Mat Blobs::Get_img_sep() const{return img_sep;}
cv::Mat Blobs::Get_img_blobs() const{return img_blobs;}
std::vector <cv::Moments> Blobs::Get_mu() const{return mu;}
std::vector <cv::Point2f> Blobs::Get_mc() const{return mc;}
std::vector <cv::Rect> Blobs::Get_rect() const{return rect;}
void Blobs::Set_img(cv::Mat image){
	image.copyTo(img_brute);
	cvtColor(img_brute, img_HSV, CV_RGB2HSV, 3);
}
