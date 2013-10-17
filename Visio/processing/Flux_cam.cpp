#include "Flux_cam.h"

using namespace std;

// Constructeurs
Flux_cam::Flux_cam(){Init(-1, 40);}
Flux_cam::Flux_cam(const int num_device, const int delais){Init(num_device, delais);}
Flux_cam::Flux_cam(const int num_device, const int delais, const int code_couleur, const int lissage){
	Init(num_device, delais, code_couleur, lissage);
}

// Initialisations transitoires
void Flux_cam::Init(const int num_device, const int delais){
	Init(num_device, delais, -1, -1);
}

// Initialisation complète de la classe (automatique à la construction)
void Flux_cam::Init(const int num_device, const int delais, const int code_couleur, const int lissage){
	capture = cv::VideoCapture(num_device);
	this->delais = delais;
	this->code_couleur = code_couleur;
	this->lissage = lissage;
	if(lissage > 1){flou_kern = cv::Size(lissage, lissage);}
	key = 'a';
	Recuperer();
}

// Récupérer une frame
void Flux_cam::Recuperer(){
	if(key != 'q'){capture >> img_cam;}
	if(code_couleur > 0){cvtColor(img_cam, img_next, code_couleur, 1);}
	else{img_cam.copyTo(img_next);}
	if(lissage > 1){blur(img_next, img_next, flou_kern, cv::Point(-1, -1), cv::BORDER_DEFAULT);}
}

// Attendre et tester si le péripérique est toujours disponible
void Flux_cam::Attendre(const int millis){
	key = cvWaitKey(millis);
	if(!capture.isOpened()){key = 'q';}
}

// Sauvegarder l'image précédente
void Flux_cam::Sauvegarder(){img_next.copyTo(img_prev);}

// Opération permise de l'extérieur
void Flux_cam::Update(){
	Sauvegarder();
	Recuperer();
	Attendre(delais);
}

// Guetters
char Flux_cam::Get_key() const{return key;}
cv::Mat Flux_cam::Get_cam() const{return img_cam;}
cv::Mat Flux_cam::Get_prev() const{return img_prev;}
cv::Mat Flux_cam::Get_next() const{return img_next;}
