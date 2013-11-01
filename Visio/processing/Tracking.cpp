#include "Tracking.h"

using namespace std;

// Constructeurs
Tracking::Tracking(){;}

// Trouver les points à tracker dans l'image suivante
void Tracking::Tracker(){


}

// Setters
void Tracking::Set_img_prev(cv::Mat image){
	image.copyTo(img_prev);
	cvtColor(img_prev, img_prev_nvg, CV_RGB2GRAY, 1);
}
void Tracking::Set_img_next(cv::Mat image){
	image.copyTo(img_next);
	cvtColor(img_next, img_next_nvg, CV_RGB2GRAY, 1);
}
void Tracking::Set_amers(std::vector <cv::Point2f> amers){this->amers = amers;}
