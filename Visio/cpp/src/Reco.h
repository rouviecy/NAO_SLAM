/*
 * @(#)		Reco.h
 * @version	1.4
 * @autor	C. Rouvière
 */

/**
 * Classe de reconnaissance de formes
 */

#ifndef RECO
#define RECO

#include <opencv2/opencv.hpp>
#include "Utils.h"

#include <set>

class Reco{

public:

	Reco();

	void Set_img(cv::Mat image);
	void Set_blobs_1(std::vector <cv::Point2f> blobs_1);
	void Set_blobs_2(std::vector <cv::Point2f> blobs_2);
	void Set_size(cv::Size taille);

	cv::Mat Get_img_quadrillage() const;
	std::vector < std::vector <cv::Point2f> > Get_quadrillage() const;
	void Detecter_quadrillage();
	std::vector <bool> Test_circle();
	std::vector <cv::Point2f> Test_inclusion(const int dist_max);

private:

	cv::Scalar bleu, blanc, rouge, cyan, jaune;
	cv::Size taille;
	cv::Mat rond;
	std::vector <cv::Point2f> blobs_1;
	std::vector <cv::Point2f> blobs_2;
	cv::Mat image, image_quadrillage;
	cv::Mat mat_1, mat_2;
	cv::Mat mat_blobs_1, mat_blobs_2;
	cv::Mat mat_compare;
	std::vector <std::vector <cv::Point2i> > liste_blobs;
	std::vector <cv::Vec4i> hierarchie_blobs;
	std::vector <cv::Moments> mu;
	std::vector <cv::Point2f> mc;
	std::vector < std::vector <cv::Point2f> > liste_quadrillage;

	cv::Point2f Intersection(cv::Vec4i a, cv::Vec4i b, int coeff) const;
	bool Confondus(cv::Vec4i a, cv::Vec4i b) const;
	void Update_mats(const int rayon);
	std::vector <int> Liste_edges_int(cv::Subdiv2D s, int max_x, int max_y, cv::Mat image);

};

#endif
