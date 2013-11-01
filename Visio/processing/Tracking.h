/*
 * @(#)		Tracking.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Classe calculant le mouvement entre deux images consécutives
 */

#ifndef TRACKING
#define TRACKING

#include <opencv/cv.h>
#include <opencv/highgui.h>

class Tracking{

public:

	Tracking();

	void Set_img_prev(cv::Mat img_prev);			// setter image N-1
	void Set_img_next(cv::Mat img_next);			// setter image N
	void Set_amers(std::vector <cv::Point2f> amers);	// setter des points à tracker
	std::vector <cv::Point2f> Get_amers() const;		// getter des points à tracker valides
	std::vector <cv::Point2f> Get_nv() const;		// getter des points trouvés

	void Tracker();						// trouver les points à tracker dans l'image suivante


private:

	cv::Mat img_prev;			// image N-1	HSV
	cv::Mat img_next;			// image N	HSV
	cv::Mat img_prev_nvg;			// image N-1	niveaux de gris
	cv::Mat img_next_nvg;			// image N	niveaux de gris
	std::vector <cv::Point2f> amers;	// points à trackers
	std::vector <cv::Point2f> nv;		// points à repérer
	std::vector <uchar> status;		// si les points ont été repérés
	std::vector <float> err;		// erreur

};

#endif
