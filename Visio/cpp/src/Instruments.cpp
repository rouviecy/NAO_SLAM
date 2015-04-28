#include "Instruments.h"

using namespace std;

// Constructeur
Instruments::Instruments(int hist_width, int hist_height){
	this->hist_width = hist_width;
	this->hist_height = hist_height;
	this->img_degrade = cv::Mat(hist_width, hist_height, CV_8UC3, cv::Scalar(0, 0, 0));
	for(int i = 0; i < hist_height; i++){
		int couleur = (180 * i) / hist_height;
		cv::Scalar pixel(couleur, 255, 255);
		img_degrade.col(i) += pixel;
	}
	cv::cvtColor(img_degrade, img_degrade, CV_HSV2RGB, 3);
	this->noir = cv::Scalar(0, 0, 0);
}

// Calculer l'histogramme en H
void Instruments::Calculer_hist_H(int nb_elems){

	float range[] = {0, 180};
	const float* histRange = {range};
	bool uniform = true;
	bool accumulate = false;

	cv::Mat img_hsv;
	cv::cvtColor(img_brute, img_hsv, CV_RGB2HSV, 3);
	vector <cv::Mat> hsv_planes;
	cv::split(img_hsv, hsv_planes);
	cv::calcHist(&hsv_planes[0], 1, 0, cv::Mat(), hist_H, 1, &nb_elems, &histRange, uniform, accumulate);

	int bin_w = round((double) hist_width/nb_elems);
	Colorier();
	cv::normalize(hist_H, hist_H, 0, img_hist_H.rows, cv::NORM_MINMAX, -1, cv::Mat());

	cv::Point sommets_polygone[1][nb_elems + 2];
	sommets_polygone[0][nb_elems] = cv::Point(hist_width, 0);
	sommets_polygone[0][nb_elems + 1] = cv::Point(0, 0);
	for(int i = 0; i < nb_elems; i++){
		sommets_polygone[0][i] = cv::Point(bin_w*(i), hist_height - round(hist_H.at<float>(i)));
	}
	const cv::Point* ppt[1] = {sommets_polygone[0]};
	int npt[] = {nb_elems + 2};
	cv::fillPoly(img_hist_H, ppt, npt, 1, noir, 8);

}

void Instruments::Colorier(){
	img_degrade.copyTo(img_hist_H);
}

// Guetters et setters
void Instruments::Set_img(cv::Mat image){this->img_brute = image;}
cv::Mat Instruments::Get_hist_H(){return img_hist_H;}
