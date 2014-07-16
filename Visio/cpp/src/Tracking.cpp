#include "Tracking.h"

using namespace std;

// Constructeurs
Tracking::Tracking(const int vitesse_max){
	this->vitesse_max = vitesse_max;
	critere = cv::TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 50, 0.03);
}

// Trouver les points à tracker dans l'image suivante
bool Tracking::Tracker(){
	nv.clear();
	if(amers.size() <= 0){return false;}
	calcOpticalFlowPyrLK(img_prev_nvg, img_next_nvg, amers, nv, status, err);
	for(size_t i = 0; i < amers.size();){
		if(status[i] != 1 || Utils::Distance_carree(amers[i].x, amers[i].y, nv[i].x, nv[i].y) > vitesse_max){
			amers.erase(amers.begin() + i);
			nv.erase(nv.begin() + i);
			status.erase(status.begin() + i);
		}
		else{i++;}
	}
	return true;
}

// Générer des amers intéressants
void Tracking::GoodFeatures(const int nb_max_amers){
	cv::goodFeaturesToTrack(img_prev_nvg, amers, nb_max_amers, 0.01, 10);
	if(amers.size() <= 0){return;}
	cv::cornerSubPix(img_prev_nvg, amers, cv::Size(5, 5), cv::Size(-1, -1), critere);
}

// Vérifier si les deux images dans le buffer sont similaires, avec les 4 rotations possibles
bool Tracking::Try_match(){
	GoodFeatures(10);
	if(amers.size() < 10){cout << "error" << endl;}
	orientation = -1;
	cv::Mat rot_90 = cv::getRotationMatrix2D(cv::Point2f(img_next.size().width / 2, img_next.size().height / 2), 90, 1);
	for(int i = 0; i < 4; i++){
		Tracker();
		if(Get_nv().size() > 5){
			orientation = i;
			return true;
		}
		cv::warpAffine(img_next, img_next, rot_90, img_next.size());
	}
	return false;
}

// Getters et Setters
void Tracking::Set_img_prev(cv::Mat image){
	image.copyTo(img_prev);
	cv::cvtColor(img_prev, img_prev_nvg, CV_RGB2GRAY, 1);
}
void Tracking::Set_img_next(cv::Mat image){
	image.copyTo(img_next);
	cv::cvtColor(img_next, img_next_nvg, CV_RGB2GRAY, 1);
}
void Tracking::Set_amers(std::vector <cv::Point2f> amers){this->amers = amers;}
std::vector <cv::Point2f> Tracking::Get_amers() const{return amers;}
std::vector <cv::Point2f> Tracking::Get_nv() const{return nv;}
int Tracking::Get_orientation() const{return orientation;}
