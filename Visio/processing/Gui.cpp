#include "Gui.h"

#define sign(n) ( (n) < 0 ? -1 : ( (n) > 1 ? 1 : 0 ) )

using namespace std;

// Constructeur - Destructeur
Gui::Gui(){
	rouge = cv::Scalar(0, 0, 255);
	dim_1 = cv::Size(1, 1);
	pod_centre = cv::Point(TAILLE_POD / 2, TAILLE_POD / 2);
	hsv = (STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
}

Gui::~Gui(){
	free(hsv);
}

// Créer des trackbars pour une séparation des couleurs en HSV
void Gui::Creer_trackbar_HSV_sep(const char* titre_fenetre){
	cv::namedWindow(titre_fenetre, CV_WINDOW_AUTOSIZE);
	hsv->winname = (schar*) titre_fenetre; hsv->name_seuil = (schar*) "seuil";
	hsv->H_min = 0; hsv->H_max = 0; hsv->S_min = 0; hsv->S_max = 0; hsv->V_min = 0; hsv->V_max = 0;
	hsv->name_H_min = (schar*) "H_min"; hsv->name_S_min = (schar*) "S_min"; hsv->name_V_min = (schar*) "V_min";
	hsv->name_H_max = (schar*) "H_max"; hsv->name_S_max = (schar*) "S_max"; hsv->name_V_max = (schar*) "V_max";
	cv::createTrackbar((char*) hsv->name_H_min, (char*) hsv->winname, &(hsv->H_min), 180, Callback_HSV, hsv);
	cv::createTrackbar((char*) hsv->name_H_max, (char*) hsv->winname, &(hsv->H_max), 180, Callback_HSV, hsv);
	cv::createTrackbar((char*) hsv->name_S_min, (char*) hsv->winname, &(hsv->S_min), 255, Callback_HSV, hsv);
	cv::createTrackbar((char*) hsv->name_S_max, (char*) hsv->winname, &(hsv->S_max), 255, Callback_HSV, hsv);
	cv::createTrackbar((char*) hsv->name_V_min, (char*) hsv->winname, &(hsv->V_min), 255, Callback_HSV, hsv);
	cv::createTrackbar((char*) hsv->name_V_max, (char*) hsv->winname, &(hsv->V_max), 255, Callback_HSV, hsv);
	cv::createTrackbar((char*) hsv->name_seuil, (char*) hsv->winname, &(hsv->seuil), 9999, Callback_HSV, hsv);
}

// Callback des trackbars
void Gui::Callback_HSV(int value, void *object){
	STRUCT_HSV_BOUND *arg = (STRUCT_HSV_BOUND*)object;
	if(arg->H_min > arg->H_max){cv::setTrackbarPos((char*) arg->name_H_max, (char*) arg->winname, arg->H_min);};
	if(arg->S_min > arg->S_max){cv::setTrackbarPos((char*) arg->name_S_max, (char*) arg->winname, arg->S_min);};
	if(arg->V_min > arg->V_max){cv::setTrackbarPos((char*) arg->name_V_max, (char*) arg->winname, arg->V_min);};
	cv::Mat img_color = cv::Mat::zeros(100, 300, CV_8UC3);
	cv::rectangle(img_color, cv::Point(0, 0), cv::Point(150, 100), cv::Scalar(arg->H_min, arg->S_min, arg->V_min), CV_FILLED);
	cv::rectangle(img_color, cv::Point(150, 0), cv::Point(300, 100), cv::Scalar(arg->H_max, arg->S_max, arg->V_max), CV_FILLED);
	cvtColor(img_color, img_color, CV_HSV2RGB, 3);
	imshow((char*) arg->winname, img_color);
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
