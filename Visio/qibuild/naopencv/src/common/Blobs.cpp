#include "Blobs.h"

using namespace std;

// Constructeur
Blobs::Blobs(){
	rouge = cv::Scalar(0, 0, 255); bleu = cv::Scalar(255, 0, 0);
	morpho_kern = cv::Mat::ones(cv::Size(3,3), CV_8U);
	seuil_taille_blobs = 42;
	STRUCT_HSV_BOUND *hsv = (STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	hsv->H_min =		0;
	hsv->H_max =		180;
	hsv->S_min =		0;
	hsv->S_max =		255;
	hsv->V_min =		10;
	hsv->V_max =		255;
	hsv->nb_dilate =	0;
	hsv->nb_erode =		0;
	Definir_limites_separation(hsv);
	free(hsv);
}

// Séparateur de couleurs et appliquer les filtres morphologiques
void Blobs::Separer(){
	if(sep_min[0] <= 180 && sep_max[0] <= 180){
		cv::inRange(img_HSV, sep_min, sep_max, img_sep);
	}
	else if (sep_min[0] > 180 && sep_max[0] > 180){
		cv::Scalar sep_min_rectif(sep_min[0] - 180, sep_min[1], sep_min[2]);
		cv::Scalar sep_max_rectif(sep_max[0] - 180, sep_max[1], sep_max[2]);
		cv::inRange(img_HSV, sep_min_rectif, sep_max_rectif, img_sep);
	}
	else{
		cv::Scalar sep_180(180, sep_max[1], sep_max[2]);
		cv::Scalar sep_0(0, sep_min[1], sep_min[2]);
		cv::Scalar sep_min_rectif(sep_min[0] - 180, sep_min[1], sep_min[2]);
		cv::Scalar sep_max_rectif(sep_max[0] - 180, sep_max[1], sep_max[2]);
		cv::Mat img_low, img_high;
		cv::inRange(img_HSV, sep_0, sep_max_rectif, img_low);
		cv::inRange(img_HSV, sep_min_rectif, sep_180, img_high);
		img_sep = img_low | img_high;
	}
	if(nb_dilate > 0)	{cv::dilate(img_sep, img_sep, morpho_kern, cv::Point(-1, -1), nb_dilate);}
	if(nb_erode > 0)	{cv::erode(img_sep, img_sep, morpho_kern, cv::Point(-1, -1), nb_erode);}
}

// Mise à jour des paramètres de segmentation HSV
void Blobs::Definir_limites_separation(STRUCT_HSV_BOUND *hsv){
	sep_min = cv::Scalar(hsv->H_min, hsv->S_min, hsv->V_min);
	sep_max = cv::Scalar(hsv->H_max, hsv->S_max, hsv->V_max);
	seuil_taille_blobs = hsv->seuil;
	nb_dilate = hsv->nb_dilate; nb_erode = hsv->nb_erode;
}

// Séparer les blobs
void Blobs::Trouver_blobs(){
	int nb_blobs = 0;
	index_best = 0; aire_best = 0;
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
		if(aire > aire_best){
			aire_best = aire;
			index_best = nb_blobs;
		}
		nb_blobs++;
		mu.push_back(mu_[i]);
		mc.push_back(mc_[i]);
		rect.push_back(rect_[i]);
		cv::drawContours(img_blobs, liste_blobs, i, bleu, CV_FILLED, 8, hierarchie_blobs);
		cv::circle(img_blobs, mc_[i], 4, rouge, -1, 8, 0);
		cv::rectangle(img_blobs, rect_[i], rouge);
	}
}

// Relier les centres de masse des blobs
void Blobs::Relier(){
	for(size_t i = 0 ; i < mc.size(); i++){
		for(size_t j = 0 ; j < mc.size(); j++){
			cv::line(img_blobs, mc[i], mc[j], rouge);
		}
	}
}

// Getters et Setters
cv::Mat Blobs::Get_img_sep() const{return img_sep;}
cv::Mat Blobs::Get_img_blobs() const{return img_blobs;}
vector <cv::Moments> Blobs::Get_mu() const{return mu;}
vector <cv::Point2f> Blobs::Get_mc() const{return mc;}
vector <cv::Rect> Blobs::Get_rect() const{return rect;}
int Blobs::Get_best_x_abs(){return (int) mc[index_best].x;}
int Blobs::Get_best_y_abs(){return (int) mc[index_best].y;}
float Blobs::Get_best_x_rel(){
	int width = img_brute.size().width;
	return (float) ((2 * Get_best_x_abs() - width) / width);
}
float Blobs::Get_best_y_rel(){
	int height = img_brute.size().height;
	return (float) ((2 * Get_best_y_abs() - height) / height);
}
double Blobs::Get_best_area() const{return aire_best;}
void Blobs::Set_img(cv::Mat image){
	image.copyTo(img_brute);
	cv::cvtColor(img_brute, img_HSV, CV_RGB2HSV, 3);
}
