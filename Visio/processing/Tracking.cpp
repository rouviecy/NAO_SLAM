#include "Tracking.h"

using namespace std;

// Constructeurs
Tracking::Tracking(int vitesse_max){
	this->vitesse_max = vitesse_max;
}

// Trouver les points à tracker dans l'image suivante
void Tracking::Tracker(){
	if(amers.size() <= 0){return;}
	calcOpticalFlowPyrLK(img_prev_nvg, img_next_nvg, amers, nv, status, err);
	for(size_t i = 0; i < amers.size();){
		if(status[i] != 1 || Distance_carree(amers[i].x, amers[i].y, nv[i].x, nv[i].y) > vitesse_max){
//		if(status[i] != 1){
			amers.erase(amers.begin() + i);
			nv.erase(nv.begin() + i);
			status.erase(status.begin() + i);
		}
		else{i++;}
	}
}

// Calculer une distance au carré pour la norme 2
int Tracking::Distance_carree(int x1, int y1, int x2, int y2){
	int dx = x2 - x1, dy = y2 - y1;
	return dx*dx + dy*dy;
}

// Getters et Setters
void Tracking::Set_img_prev(cv::Mat image){
	image.copyTo(img_prev);
	cvtColor(img_prev, img_prev_nvg, CV_RGB2GRAY, 1);
}
void Tracking::Set_img_next(cv::Mat image){
	image.copyTo(img_next);
	cvtColor(img_next, img_next_nvg, CV_RGB2GRAY, 1);
}
void Tracking::Set_amers(std::vector <cv::Point2f> amers){this->amers = amers;}
std::vector <cv::Point2f> Tracking::Get_amers() const{return amers;}
std::vector <cv::Point2f> Tracking::Get_nv() const{return nv;}
