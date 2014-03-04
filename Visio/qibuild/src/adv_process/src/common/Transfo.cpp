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
	size_t NB = 5;
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
	int tab_position_bords[4][2];
	tab_position_bords[0][0] = 0;				tab_position_bords[0][1] = 0;
	tab_position_bords[1][0] = img_brute.size().width;	tab_position_bords[1][1] = 0;
	tab_position_bords[2][0] = 0;				tab_position_bords[2][1] = img_brute.size().height;
	tab_position_bords[3][0] = img_brute.size().width;	tab_position_bords[3][1] = img_brute.size().height;
	int dist_diag = img_brute.size().width * img_brute.size().width + img_brute.size().height * img_brute.size().height;
	for(int j = 0; j < 4; j++){
		int dist_min = dist_diag;
		for(size_t i = 0; i < NB; i++){
			int dist = Utils::Distance_carree(pts_input[i].x, pts_input[i].y, tab_position_bords[j][0], tab_position_bords[j][1]);
			if(dist < dist_min){
				dist_min = dist;
				tab_index[j] = i;
			}
		}
	}
	vector <cv::Point2f> pts1, pts2;
	for(int j = 0; j < 4; j++){
		pts1.push_back(cv::Point2f(tab_position_bords[j][0], tab_position_bords[j][1]));
		pts2.push_back(pts_input[tab_index[j]]);
	}
	cv::Mat M = cv::getPerspectiveTransform(pts2, pts1);
	cv::warpPerspective(img_brute, img_wrap, M, img_brute.size());
	int index_centre = 10 - tab_index[0] - tab_index[1] - tab_index[2] - tab_index[3];
	vector <cv::Point2f> tempo;
	tempo.push_back(pts_input[index_centre]);
	cv::perspectiveTransform(tempo, center, M);
}

// Getters et Setters
cv::Mat Transfo::Get_img_wrap() const{return img_wrap;}
vector <cv::Point2f> Transfo::Get_center() const{return center;}
void Transfo::Set_img(cv::Mat image){image.copyTo(img_brute);}
void Transfo::Set_pts_redressement(vector <cv::Point2f> pts_input){this->pts_input = pts_input;}
