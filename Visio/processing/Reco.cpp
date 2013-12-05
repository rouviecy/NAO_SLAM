#include "Reco.h"

using namespace std;

// Constructeur
Reco::Reco(){

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
	vector <cv::Point2f> result;
	for(vector <cv::Point2f> ::iterator blob1 = blobs_1.begin(); blob1 != blobs_1.end(); ++blob1){
		for(vector <cv::Point2f> ::iterator blob2 = blobs_2.begin(); blob2 != blobs_2.end(); ++blob2){
			if(Utils::Distance_carree((*blob1).x, (*blob1).y, (*blob2).x, (*blob2).y) < dist_max){
				result.push_back(*blob1);
			}
		}
	}
	return result;
}

// Mettre à jour les matrices des blobs
void Reco::Update_mats(){
	mat_blobs_1 = cv::Mat::zeros(width, height, CV_8UC1);
	mat_blobs_2 = cv::Mat::zeros(width, height, CV_8UC1);
	for(vector <cv::Point2f> ::iterator blob = blobs_1.begin(); blob != blobs_1.end(); ++blob){

	}
	for(vector <cv::Point2f> ::iterator blob = blobs_2.begin(); blob != blobs_2.end(); ++blob){

	}
}

// Getters et Setters
void Reco::Set_blobs_1(std::vector <cv::Point2f> blobs_1){this->blobs_1 = blobs_1;}
void Reco::Set_blobs_2(std::vector <cv::Point2f> blobs_2){this->blobs_2 = blobs_2;}
void Reco::Set_size(int width, int height){this->width = width; this->height = height;}
