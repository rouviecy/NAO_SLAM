#include "Transfo.h"

using namespace std;

// Constructeur
Transfo::Transfo(){
	x1 = 0; y1 = 0; x2 = 180; y2 = 0; x3 = 0; y3 = 180; x4 = 180; y4 = 180;
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
	vector <cv::Point2f> pts_in, pts_out;
	pts_in.push_back(cv::Point2f(0, 0));
	pts_in.push_back(cv::Point2f(180, 0));
	pts_in.push_back(cv::Point2f(0, 180));
	pts_in.push_back(cv::Point2f(180, 180));
	pts_out.push_back(cv::Point2f(x1, y1));
	pts_out.push_back(cv::Point2f(x2, y2));
	pts_out.push_back(cv::Point2f(x3, y3));
	pts_out.push_back(cv::Point2f(x4, y4));
	cv::Mat M = cv::getPerspectiveTransform(pts_in, pts_out);
	warpPerspective(img_brute, img_wrap, M, img_brute.size());
}

// Getters et Setters
cv::Mat Transfo::Get_img_wrap() const{return img_wrap;}
void Transfo::Set_img(cv::Mat image){image.copyTo(img_brute);}
