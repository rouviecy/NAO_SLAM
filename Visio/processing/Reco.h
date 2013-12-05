/*
 * @(#)		Reco.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Classe de reconnaissance de formes
 */

#ifndef RECO
#define RECO

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "Utils.h"

class Reco{

public:

	Reco();

	void Set_size(int width, int height);
	void Set_blobs_1(std::vector <cv::Point2f> blobs_1);
	void Set_blobs_2(std::vector <cv::Point2f> blobs_2);

	std::vector <bool> Test_circle();
	std::vector <cv::Point2f> Test_inclusion(const int dist_max);

private:

	std::vector <cv::Point2f> blobs_1;
	std::vector <cv::Point2f> blobs_2;
	cv::Mat mat_blobs_1;
	cv::Mat mat_blobs_2;

	int width;
	int height;

	void Update_mats();

};

#endif
