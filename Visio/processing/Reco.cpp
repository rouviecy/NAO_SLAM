#include "Reco.h"

using namespace std;

// Constructeur
Reco::Reco(){

}

// Tests de reconnaissance de cercle
std::vector <bool> Reco::Test_circle(){
	vector <bool> result;
	for(size_t i = 0; i < blobs_1.size(); i++){
		// TODO : travailler avec blobs_1(blobs_1.begin() + i)
	}
	return result;
}

// Test de reconnaissance de blob dans un blob
std::vector <int[2]> Reco::Test_inclusion(){
	vector <int[2]> result;
	for(size_t i = 0; i < blobs_1.size(); i++){
		for(size_t j = 0; j < blobs_2.size(); j++){
			// TODO : travailler avec blobs_1(blobs_1.begin() + i)
			// TODO : travailler avec blobs_2(blobs_2.begin() + j)
		}
	}
	return result;
}

// Getters et Setters
void Reco::Set_blobs_1(std::vector <cv::Point2i> blobs_1){this->blobs_1 = blobs_1;}
void Reco::Set_blobs_2(std::vector <cv::Point2i> blobs_2){this->blobs_2 = blobs_2;}
