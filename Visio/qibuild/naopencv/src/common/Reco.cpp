#include "Reco.h"

using namespace std;

// Constructeur
Reco::Reco(){
	blanc = cv::Scalar(255);
}

// Tests de reconnaissance de cercle
std::vector <bool> Reco::Test_circle(){
	vector <bool> result;
	for(vector <cv::Point2f> ::iterator blob = blobs_1.begin(); blob != blobs_1.end(); ++blob){
		// TODO : travailler avec blob
	}
	return result;
}

// Test de reconnaissance de blob dans un blob
std::vector <cv::Point2f> Reco::Test_inclusion(const int dist_max){
	mu.clear(), mc.clear();
	Update_mats((int) dist_max / 2);
	mat_compare = mat_blobs_1 & mat_blobs_2;
	cv::findContours(mat_compare, liste_blobs, hierarchie_blobs, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	if(hierarchie_blobs.size() <= 0){return mc;}
	for(size_t i = 0; i < liste_blobs.size(); i++){
		mu.push_back(cv::moments(liste_blobs[i], false));
		mc.push_back(cv::Point2f(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00));
	}
	return mc;
}

// Mettre à jour les matrices des blobs
void Reco::Update_mats(const int rayon){
	mat_1 = cv::Mat::zeros(taille, CV_8U);
	mat_2 = cv::Mat::zeros(taille, CV_8U);
	for(vector <cv::Point2f> ::iterator blob = blobs_1.begin(); blob != blobs_1.end(); ++blob){
		cv::circle(mat_1, cv::Point2i((int) floor((*blob).x), (int) floor((*blob).y)), rayon, blanc, -1, 8, 0);
	}
	for(vector <cv::Point2f> ::iterator blob = blobs_2.begin(); blob != blobs_2.end(); ++blob){
		cv::circle(mat_2, cv::Point2i((int) floor((*blob).x), (int) floor((*blob).y)), rayon, blanc, -1, 8, 0);
	}
	cv::Scalar mini(42); cv::Scalar maxi(255);
	cv::inRange(mat_1, mini, maxi, mat_blobs_1);
	cv::inRange(mat_2, mini, maxi, mat_blobs_2);
}

// Getters et Setters
void Reco::Set_blobs_1(const vector <cv::Point2f> blobs_1){this->blobs_1 = blobs_1;}
void Reco::Set_blobs_2(const vector <cv::Point2f> blobs_2){this->blobs_2 = blobs_2;}
void Reco::Set_size(const cv::Size taille){this->taille = taille;}
