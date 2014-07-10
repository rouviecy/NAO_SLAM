#include "Instruments.h"

using namespace std;

// Constructeur
Instruments::Instruments(int hist_width, int hist_height){
	this->hist_width = hist_width;
	this->hist_height = hist_height;
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

	for(int i = 1; i < nb_elems; i++){
		cv::line(img_hist_H,
			cv::Point(bin_w*(i-1),	hist_height - round(hist_H.at<float>(i-1))),
			cv::Point(bin_w*(i),	hist_height - round(hist_H.at<float>(i))),
			cv::Scalar(255, 0, 0),
			2, 8, 0
		);
	}

}

void Instruments::Colorier(){
	img_hist_H = cv::Mat(hist_height, hist_width, CV_8UC3, cv::Scalar(0,0,0));
}

// Guetters et setters
void Instruments::Set_img(cv::Mat image){this->img_brute = image;}
cv::Mat Instruments::Get_hist_H(){return img_hist_H;}
