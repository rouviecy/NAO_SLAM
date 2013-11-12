#include "Transfo.h"

using namespace std;

// Constructeur
Transfo::Transfo(){
	x1 = 0; y1 = 0; x2 = 180; y2 = 0; x3 = 0; y3 = 180; x4 = 180; y4 = 180;
	deja = false;
}

// Mise à jour des paramètres de transformation
void Transfo::Definir_parametres_transformation(STRUCT_WRAP_BOUND *wrap){
	x1 = wrap->x1; y1 = wrap->y1;
	x2 = wrap->x2; y2 = wrap->y2;
	x3 = wrap->x3; y3 = wrap->y3;
	x4 = wrap->x4; y4 = wrap->y4;
}

// Perspective
void Transfo::Appliquer_wrap(){
	center.clear();
	int NB = 5;
	if(deja == false){img_brute.copyTo(img_wrap); deja = true;}
/*	vector <cv::Point2f> pts_in, pts_out;
	pts_in.push_back(cv::Point2f(0, 0));
	pts_in.push_back(cv::Point2f(180, 0));
	pts_in.push_back(cv::Point2f(0, 180));
	pts_in.push_back(cv::Point2f(180, 180));
	pts_out.push_back(cv::Point2f(x1, y1));
	pts_out.push_back(cv::Point2f(x2, y2));
	pts_out.push_back(cv::Point2f(x3, y3));
	pts_out.push_back(cv::Point2f(x4, y4));
	cv::Mat M = cv::getPerspectiveTransform(pts_in, pts_out);
*/	if(pts_input.size() != NB){return;}
	int tab_index[4];
	int dist_min = img_brute.size().width * img_brute.size().width + img_brute.size().height * img_brute.size().height;
	for(size_t i = 0; i < NB; i++){
		int dist = Utils::Distance_carree(pts_input[i].x, pts_input[i].y, 0, 0);
		if(dist < dist_min){
			dist_min = dist;
			tab_index[0] = i;
		}
	}
	dist_min = img_brute.size().width * img_brute.size().width + img_brute.size().height * img_brute.size().height;
	for(size_t i = 0; i < NB; i++){
		int dist = Utils::Distance_carree(pts_input[i].x, pts_input[i].y, img_brute.size().width, 0);
		if(dist < dist_min){
			dist_min = dist;
			tab_index[1] = i;
		}
	}
	dist_min = img_brute.size().width * img_brute.size().width + img_brute.size().height * img_brute.size().height;
	for(size_t i = 0; i < NB; i++){
		int dist = Utils::Distance_carree(pts_input[i].x, pts_input[i].y, 0, img_brute.size().height);
		if(dist < dist_min){
			dist_min = dist;
			tab_index[2] = i;
		}
	}
	dist_min = img_brute.size().width * img_brute.size().width + img_brute.size().height * img_brute.size().height;
	for(size_t i = 0; i < NB; i++){
		int dist = Utils::Distance_carree(pts_input[i].x, pts_input[i].y, img_brute.size().width, img_brute.size().height);
		if(dist < dist_min){
			dist_min = dist;
			tab_index[3] = i;
		}
	}
	vector <cv::Point2f> pts1, pts2;
	pts1.push_back(cv::Point2f(0, 0));
	pts1.push_back(cv::Point2f(img_brute.size().width, 0));
	pts1.push_back(cv::Point2f(0, img_brute.size().height));
	pts1.push_back(cv::Point2f(img_brute.size().width, img_brute.size().height));
	pts2.push_back(pts_input[tab_index[0]]);
	pts2.push_back(pts_input[tab_index[1]]);
	pts2.push_back(pts_input[tab_index[2]]);
	pts2.push_back(pts_input[tab_index[3]]);
	cv::Mat M = cv::getPerspectiveTransform(pts2, pts1);
	warpPerspective(img_brute, img_wrap, M, img_brute.size());
	int index_centre = 10 - tab_index[0] - tab_index[1] - tab_index[2] - tab_index[3];
	vector <cv::Point2f> tempo;
	tempo.push_back(pts_input[index_centre]);
	perspectiveTransform(tempo, center, M);
}

// Getters et Setters
cv::Mat Transfo::Get_img_wrap() const{return img_wrap;}
vector <cv::Point2f> Transfo::Get_center() const{return center;}
void Transfo::Set_img(cv::Mat image){image.copyTo(img_brute);}
void Transfo::Set_pts_redressement(vector <cv::Point2f> pts_input){this->pts_input = pts_input;}
