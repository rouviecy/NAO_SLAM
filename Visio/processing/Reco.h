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

class Reco{

public:

	Reco();
	void Set_blobs_1(std::vector <cv::Point2i> blobs_1);

private:

	std::vector <cv::Point2i> blobs_1;

};

#endif
