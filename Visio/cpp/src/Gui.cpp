#include "Gui.h"

#define sign(n) ( (n) < 0 ? -1 : ( (n) > 1 ? 1 : 0 ) )

using namespace std;

// Constructeur - Destructeur
Gui::Gui(){
	rouge = cv::Scalar(0, 0, 255);
	dim_1 = cv::Size(1, 1);
	pod_centre = cv::Point(TAILLE_POD / 2, TAILLE_POD / 2);
	hsv = (hsv_params*) malloc(sizeof(hsv_params));
	hsv2 = (hsv_params*) malloc(sizeof(hsv_params));
	wrap = (STRUCT_WRAP_BOUND*) malloc(sizeof(STRUCT_WRAP_BOUND));
	dpy = XOpenDisplay(0);
	root_window = XRootWindow(dpy, 0);
	XSelectInput(dpy, root_window, KeyReleaseMask);
	buttonCount = XGetPointerMapping(dpy, buttonMap, 3);
}

Gui::~Gui(){
	free(hsv);
	free(hsv2);
}

void Gui::Creer_trackbar_HSV_sep(const char* titre_fenetre){
	cv::namedWindow(titre_fenetre, CV_WINDOW_AUTOSIZE);
	strcpy(hsv->winname, titre_fenetre);
	hsv->H_min = 0; hsv->H_max = 0; hsv->S_min = 0; hsv->S_max = 0; hsv->V_min = 0; hsv->V_max = 0; hsv->seuil = 0;
	hsv->nb_dilate = 0; hsv->nb_erode = 0;
	strcpy(hsv->name_H_min, "H_min"); strcpy(hsv->name_S_min, "S_min"); strcpy(hsv->name_V_min, "V_min");
	strcpy(hsv->name_H_max, "H_max"); strcpy(hsv->name_S_max, "S_max"); strcpy(hsv->name_V_max , "V_max");
	strcpy(hsv->name_nb_dilate , "nb_dilate"); strcpy(hsv->name_nb_erode, "nb_erode"); strcpy(hsv->name_seuil, "seuil");
	cv::createTrackbar(hsv->name_H_min, hsv->winname, &(hsv->H_min), 360, Callback_HSV, hsv);
	cv::createTrackbar(hsv->name_H_max, hsv->winname, &(hsv->H_max), 360, Callback_HSV, hsv);
	cv::createTrackbar(hsv->name_S_min, hsv->winname, &(hsv->S_min), 255, Callback_HSV, hsv);
	cv::createTrackbar(hsv->name_S_max, hsv->winname, &(hsv->S_max), 255, Callback_HSV, hsv);
	cv::createTrackbar(hsv->name_V_min, hsv->winname, &(hsv->V_min), 255, Callback_HSV, hsv);
	cv::createTrackbar(hsv->name_V_max, hsv->winname, &(hsv->V_max), 255, Callback_HSV, hsv);
	cv::createTrackbar(hsv->name_seuil, hsv->winname, &(hsv->seuil), 9999, Callback_HSV, hsv);
	cv::createTrackbar(hsv->name_nb_dilate, hsv->winname, &(hsv->nb_dilate), 20, Callback_HSV, hsv);
	cv::createTrackbar(hsv->name_nb_erode, hsv->winname, &(hsv->nb_erode), 20, Callback_HSV, hsv);
}

void Gui::Creer_trackbar_HSV_sep2(const char* titre_fenetre){
	cv::namedWindow(titre_fenetre, CV_WINDOW_AUTOSIZE);
	strcpy(hsv2->winname, titre_fenetre);
	hsv2->H_min = 0; hsv2->H_max = 0; hsv2->S_min = 0; hsv2->S_max = 0; hsv2->V_min = 0; hsv2->V_max = 0; hsv2->seuil = 0;
	hsv2->nb_dilate = 0; hsv2->nb_erode = 0;
	strcpy(hsv2->name_H_min, "H_min"); strcpy(hsv2->name_S_min, "S_min"); strcpy(hsv2->name_V_min, "V_min");
	strcpy(hsv2->name_H_max, "H_max"); strcpy(hsv2->name_S_max, "S_max"); strcpy(hsv2->name_V_max , "V_max");
	strcpy(hsv2->name_nb_dilate , "nb_dilate"); strcpy(hsv2->name_nb_erode, "nb_erode"); strcpy(hsv2->name_seuil, "seuil");
	cv::createTrackbar(hsv2->name_H_min, hsv2->winname, &(hsv2->H_min), 360, Callback_HSV, hsv2);
	cv::createTrackbar(hsv2->name_H_max, hsv2->winname, &(hsv2->H_max), 360, Callback_HSV, hsv2);
	cv::createTrackbar(hsv2->name_S_min, hsv2->winname, &(hsv2->S_min), 255, Callback_HSV, hsv2);
	cv::createTrackbar(hsv2->name_S_max, hsv2->winname, &(hsv2->S_max), 255, Callback_HSV, hsv2);
	cv::createTrackbar(hsv2->name_V_min, hsv2->winname, &(hsv2->V_min), 255, Callback_HSV, hsv2);
	cv::createTrackbar(hsv2->name_V_max, hsv2->winname, &(hsv2->V_max), 255, Callback_HSV, hsv2);
	cv::createTrackbar(hsv2->name_seuil, hsv2->winname, &(hsv2->seuil), 9999, Callback_HSV, hsv2);
	cv::createTrackbar(hsv2->name_nb_dilate, hsv2->winname, &(hsv2->nb_dilate), 10, Callback_HSV, hsv2);
	cv::createTrackbar(hsv2->name_nb_erode, hsv2->winname, &(hsv2->nb_erode), 10, Callback_HSV, hsv2);
}
// Créer des trackbars pour les transformations
void Gui::Creer_trackbar_transfo(const char* titre_fenetre){
	cv::namedWindow(titre_fenetre, CV_WINDOW_AUTOSIZE);
	strcpy(wrap->winname, titre_fenetre);
	wrap->x1 = 0; wrap->y1 = 0; wrap->x2 = 180; wrap->y2 = 0; wrap->x3 = 0; wrap->y3 = 180; wrap->x4 = 180; wrap->y4 = 180;
	strcpy(wrap->name_x1, "x1"); strcpy(wrap->name_y1, "y1");
	strcpy(wrap->name_x2, "x2"); strcpy(wrap->name_y2, "y2");
	strcpy(wrap->name_x3, "x3"); strcpy(wrap->name_y3, "y3");
	strcpy(wrap->name_x4, "x4"); strcpy(wrap->name_y4, "y4");
	cv::createTrackbar(wrap->name_x1, wrap->winname, &(wrap->x1), 180, Callback_wrap, wrap);
	cv::createTrackbar(wrap->name_x2, wrap->winname, &(wrap->x2), 180, Callback_wrap, wrap);
	cv::createTrackbar(wrap->name_x3, wrap->winname, &(wrap->x3), 180, Callback_wrap, wrap);
	cv::createTrackbar(wrap->name_x4, wrap->winname, &(wrap->x4), 180, Callback_wrap, wrap);
	cv::createTrackbar(wrap->name_y1, wrap->winname, &(wrap->y1), 180, Callback_wrap, wrap);
	cv::createTrackbar(wrap->name_y2, wrap->winname, &(wrap->y2), 180, Callback_wrap, wrap);
	cv::createTrackbar(wrap->name_y3, wrap->winname, &(wrap->y3), 180, Callback_wrap, wrap);
	cv::createTrackbar(wrap->name_y4, wrap->winname, &(wrap->y4), 180, Callback_wrap, wrap);
}

// Callback des trackbars HSV
void Gui::Callback_HSV(int value, void *object){
	hsv_params *arg = (hsv_params*)object;
	if(arg->H_min > arg->H_max){cv::setTrackbarPos((char*) arg->name_H_max, (char*) arg->winname, arg->H_min);};
	if(arg->S_min > arg->S_max){cv::setTrackbarPos((char*) arg->name_S_max, (char*) arg->winname, arg->S_min);};
	if(arg->V_min > arg->V_max){cv::setTrackbarPos((char*) arg->name_V_max, (char*) arg->winname, arg->V_min);};
	cv::Mat img_color = cv::Mat::zeros(100, 300, CV_8UC3);
	cv::rectangle(img_color, cv::Point(0, 0), cv::Point(150, 100), cv::Scalar(arg->H_min, arg->S_min, arg->V_min), CV_FILLED);
	cv::rectangle(img_color, cv::Point(150, 0), cv::Point(300, 100), cv::Scalar(arg->H_max, arg->S_max, arg->V_max), CV_FILLED);
	cv::cvtColor(img_color, img_color, CV_HSV2RGB, 3);
	cv::imshow((char*) arg->winname, img_color);
}

// Callback des trackbars de transformation
void Gui::Callback_wrap(int value, void *object){
//	STRUCT_WRAP_BOUND *arg = (STRUCT_WRAP_BOUND*)object;
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

// Prendre le contrôle de la souris
void Gui::Controler_souris(std::vector <cv::Point2i> mc, int width, int height){
	if(mc.size() <= 0){return;}
	int XMouse = (int) ((float) mc[0].x / width * 1600);
	int YMouse = (int) ((float) mc[0].y / height * 900);
	if(XMouse > 0 && XMouse < 1600 && YMouse > 0 && YMouse < 900){
		XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, XMouse, YMouse);
		XFlush(dpy);
	}
}

// Cliquer si le vecteur d'entrée n'est pas vide
void Gui::Cliquer(std::vector <cv::Point2i> mc){XTestFakeButtonEvent(dpy, buttonMap[0], mc.size() > 0, 0);}


// Afficher une image et des vecteurs
void Gui::Ajouter_vecteurs(const std::string titre_fenetre, cv::Mat image, vector<cv::Point2i> pts_prev, vector<cv::Point2i> pts_next){
	cv::Mat img_show;
	image.copyTo(img_show);
	for(size_t i = 0; i < pts_prev.size(); i++){
		cv::Point2i p1 = pts_prev[i];
		cv::Point2i p2 = pts_next[i];
		ellipse(img_show, p1, dim_1, 0, 0, 360, rouge);
		line(img_show, p1, p2, rouge);
	}
	Afficher_image(titre_fenetre, img_show);
}

// Guetters et setters
hsv_params *Gui::Get_HSV_bound() const{return hsv;}
hsv_params *Gui::Get_HSV_bound2() const{return hsv2;}
STRUCT_WRAP_BOUND *Gui::Get_wrap_bound() const{return wrap;}
