#include "Gui.h"

#define sign(n) ( (n) < 0 ? -1 : ( (n) > 1 ? 1 : 0 ) )

using namespace std;

// Constructeur
Gui::Gui(){
	rouge = cv::Scalar(0, 0, 255);
	dim_1 = cv::Size(1, 1);
	pod_centre = cv::Point(TAILLE_POD / 2, TAILLE_POD / 2);
	hsv = (STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
}

// Créer des trackbars pour une séparation des couleurs en HSV
void Gui::Creer_trackbar_HSV_sep(const std::string titre_fenetre){
	cv::namedWindow(titre_fenetre, CV_WINDOW_AUTOSIZE);
	hsv->H_min = 0; hsv->H_max = 0; hsv->S_min = 0; hsv->S_max = 0; hsv->V_min = 0; hsv->V_max = 0;
	cv::createTrackbar("H_min", titre_fenetre, &(hsv->H_min), 180);
	cv::createTrackbar("H_max", titre_fenetre, &(hsv->H_max), 180);
	cv::createTrackbar("S_min", titre_fenetre, &(hsv->S_min), 255);
	cv::createTrackbar("S_max", titre_fenetre, &(hsv->S_max), 255);
	cv::createTrackbar("V_min", titre_fenetre, &(hsv->V_min), 255);
	cv::createTrackbar("V_max", titre_fenetre, &(hsv->V_max), 255);
}

// Afficher une image
void Gui::Afficher_image(const std::string titre_fenetre, cv::Mat image){
	imshow(titre_fenetre, image);
}

// Afficher un vecteur
void Gui::Pad(const std::string titre_fenetre, const float dx, const float dy, const float dx_max, const float dy_max){
	float delta_x_pod = abs(dx) < dx_max ? (float) TAILLE_POD * dx / (2. * dx_max) : (float) (sign(dx) * TAILLE_POD / 2);
	float delta_y_pod = abs(dy) < dy_max ? (float) TAILLE_POD * dy / (2. * dy_max) : (float) (sign(dy) * TAILLE_POD / 2);
	cv::Point pod_fin(TAILLE_POD / 2 + (int) delta_x_pod, TAILLE_POD / 2 + (int) delta_y_pod);
	cv::Mat img_show = cv::Mat::zeros(TAILLE_POD, TAILLE_POD, CV_8UC3);
	ellipse(img_show, pod_centre, dim_1, 0, 0, 360, rouge);
	line(img_show, pod_centre, pod_fin, rouge);
	Afficher_image(titre_fenetre, img_show);
}

// Afficher une image et des vecteurs
void Gui::Ajouter_vecteurs(const std::string titre_fenetre, cv::Mat image, vector<cv::Point2f> pts_prev, vector<cv::Point2f> pts_next){
	cv::Mat img_show;
	image.copyTo(img_show);
	for(size_t i = 0; i < pts_prev.size(); i++){
		cv::Point2f p1 = pts_prev[i];
		cv::Point2f p2 = pts_next[i];
		ellipse(img_show, p1, dim_1, 0, 0, 360, rouge);
		line(img_show, p1, p2, rouge);
	}
	Afficher_image(titre_fenetre, img_show);
}

// Guetters et setters
STRUCT_HSV_BOUND *Gui::Get_HSV_bound() const{return hsv;}
