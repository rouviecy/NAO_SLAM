#include "NAO_flux.h"

using namespace std;
using namespace AL;

// Constructeurs
NAO_flux::NAO_flux(){Init(-1, 40);}
NAO_flux::NAO_flux(const int num_device, const int delais){Init(num_device, delais);}
NAO_flux::NAO_flux(const int num_device, const int delais, const int code_couleur, const int lissage, const int flip){
	Init(num_device, delais, code_couleur, lissage, flip);
}

// Initialisations transitoires
void NAO_flux::Init(const int num_device, const int delais){
	Init(num_device, delais, -1, -1, 0);
}

// Initialisation complète de la classe (automatique à la construction)
void NAO_flux::Init(const int num_device, const int delais, const int code_couleur, const int lissage, const int flip){
	this->delais =		delais;
	this->code_couleur =	code_couleur;
	this->lissage =		lissage;
	this->flip =		flip;
	if(lissage > 1){flou_kern = cv::Size(lissage, lissage);}
	camProxy = ALVideoDeviceProxy("127.0.0.1", 9559);
	clientName = camProxy.subscribe("test", kQVGA, kBGRColorSpace, 30); // TODO : changer les paramètres en fonction des arg constructeur
	img_brute = cv::Mat(cv::Size(320, 240), CV_8UC3);
	key = 'a';
	Recuperer();
}

NAO_flux::~NAO_flux(){
	camProxy.unsubscribe(clientName);
}

// Récupérer une frame
void NAO_flux::Recuperer(){
	if (key != 'q'){
		ALValue img = camProxy.getImageRemote(clientName);
		img_brute.data = (uchar*) img[6].GetBinary();
		camProxy.releaseImage(clientName);
	}
	if	(flip == 1)		{cv::flip(img_cam, img_cam, 1);}
	else if	(flip == 2)		{cv::flip(img_cam, img_cam, 0);}
	else if	(flip == 3)		{cv::flip(img_cam, img_cam, -1);}
	img_cam.copyTo(img_next);
	if	(lissage > 1)		{cv::blur(img_next, img_next, flou_kern, cv::Point(-1, -1), cv::BORDER_DEFAULT);}
}

// Attendre
void NAO_flux::Attendre(const int millis){usleep(1000 * millis);}

// Sauvegarder l'image précédente
void NAO_flux::Sauvegarder(){img_next.copyTo(img_prev);}

// Opération permise de l'extérieur
void NAO_flux::Update(){
	Sauvegarder();
	Recuperer();
	Attendre(delais);
}

// Guetters
char NAO_flux::Get_key() const{return key;}
cv::Mat NAO_flux::Get_cam() const{return img_cam;}
cv::Mat NAO_flux::Get_prev() const{return img_prev;}
cv::Mat NAO_flux::Get_next() const{return img_next;}
