#include "Body.h"

using namespace std;

// Constructeur - Destructeur
Body::Body(){
	hsv_jaune =	(STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	hsv_vert =	(STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	hsv_rouge =	(STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	hsv_bleu =	(STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	hsv_rose =	(STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	blobs = new Blobs[2];
	Couleurs();
	Membres();
	Tete = cv::Point2f(0, 0);
	L_shoulder = cv::Point2f(0, 0);
	R_shoulder = cv::Point2f(0, 0);
	L_elbow = cv::Point2f(0, 0);
	R_elbow = cv::Point2f(0, 0);
	L_hand = cv::Point2f(0, 0);
	R_hand = cv::Point2f(0, 0);
	L_foot = cv::Point2f(0, 0);
	R_foot = cv::Point2f(0, 0);
}

Body::~Body(){
	free(hsv_jaune); free(hsv_vert); free(hsv_rouge); free(hsv_bleu);
	delete[] blobs;
}

// Paramètres colorimétriques
void Body::Couleurs(){
	hsv_jaune->H_min = 83;	hsv_jaune->S_min = 107;	hsv_jaune->V_min = 142;	hsv_jaune->seuil = 25;
	hsv_jaune->H_max = 93;	hsv_jaune->S_max = 255;	hsv_jaune->V_max = 255;
	hsv_vert->H_min = 58;	hsv_vert->S_min = 98;	hsv_vert->V_min = 84;	hsv_vert->seuil = 25;
	hsv_vert->H_max = 69;	hsv_vert->S_max = 255;	hsv_vert->V_max = 255;
	hsv_rouge->H_min = 114;	hsv_rouge->S_min = 63;	hsv_rouge->V_min = 39;	hsv_rouge->seuil = 25;
	hsv_rouge->H_max = 126;	hsv_rouge->S_max = 165;	hsv_rouge->V_max = 255;
	hsv_bleu->H_min = 2;	hsv_bleu->S_min = 36;	hsv_bleu->V_min = 46;	hsv_bleu->seuil = 25;
	hsv_bleu->H_max = 16;	hsv_bleu->S_max = 255;	hsv_bleu->V_max = 255;
	hsv_rose->H_min = 130;	hsv_rose->S_min = 157;	hsv_rose->V_min = 137;	hsv_rose->seuil = 25;
	hsv_rose->H_max = 138;	hsv_rose->S_max = 255;	hsv_rose->V_max = 255;
}

// Couleurs des membres
void Body::Membres(){
	hsv_Tete[0] =		hsv_bleu;	hsv_Tete[1] =		hsv_rouge;
	hsv_L_shoulder[0] =	hsv_bleu;	hsv_L_shoulder[1] =	hsv_jaune;
	hsv_R_shoulder[0] =	hsv_bleu;	hsv_R_shoulder[1] =	hsv_vert;
	hsv_L_elbow[0] =	hsv_rouge;	hsv_L_elbow[1] =	hsv_jaune;
	hsv_R_elbow[0] =	hsv_rouge;	hsv_R_elbow[1] =	hsv_vert;
	hsv_L_hand[0] =		hsv_rose;	hsv_L_hand[1] =		hsv_jaune;
	hsv_R_hand[0] =		hsv_rose;	hsv_R_hand[1] =		hsv_vert;
	hsv_L_foot[0] =		hsv_rose;	hsv_L_foot[1] =		hsv_rouge;
	hsv_R_foot[0] =		hsv_rose;	hsv_R_foot[1] =		hsv_bleu;
}

// Mettre à jour le détecteur de blobs
vector <cv::Point2f> Body::Update_blobs(){
	for(int i = 0; i < 2; i++){
		blobs[i].Set_img(img);
		blobs[i].Separer();
		blobs[i].Trouver_blobs();
	}
	reco.Set_blobs_1(blobs[0].Get_mc());
	reco.Set_blobs_2(blobs[1].Get_mc());
	return reco.Test_inclusion(10);
}

// Chercher la tête
void Body::Detecter_tete(){
	blobs[0].Definir_limites_separation(hsv_Tete[0]);
	blobs[1].Definir_limites_separation(hsv_Tete[1]);
	vector <cv::Point2f> liste = Update_blobs();
	if(liste.size() > 0){Tete = liste[0];}
}

// Chercher l'épaule gauche
void Body::Detecter_epaule_gauche(){
	blobs[0].Definir_limites_separation(hsv_L_shoulder[0]);
	blobs[1].Definir_limites_separation(hsv_L_shoulder[1]);
	vector <cv::Point2f> liste = Update_blobs();
	if(liste.size() > 0){L_shoulder = liste[0];}
}

// Chercher l'épaule droite
void Body::Detecter_epaule_droite(){
	blobs[0].Definir_limites_separation(hsv_R_shoulder[0]);
	blobs[1].Definir_limites_separation(hsv_R_shoulder[1]);
	vector <cv::Point2f> liste = Update_blobs();
	if(liste.size() > 0){R_shoulder = liste[0];}
}

// Chercher le coude gauche
void Body::Detecter_coude_gauche(){
	blobs[0].Definir_limites_separation(hsv_L_elbow[0]);
	blobs[1].Definir_limites_separation(hsv_L_elbow[1]);
	vector <cv::Point2f> liste = Update_blobs();
	if(liste.size() > 0){L_elbow = liste[0];}
}

// Chercher le coude droit
void Body::Detecter_coude_droit(){
	blobs[0].Definir_limites_separation(hsv_R_elbow[0]);
	blobs[1].Definir_limites_separation(hsv_R_elbow[1]);
	vector <cv::Point2f> liste = Update_blobs();
	if(liste.size() > 0){R_elbow = liste[0];}
}

// Chercher la main gauche
void Body::Detecter_main_gauche(){
	blobs[0].Definir_limites_separation(hsv_L_hand[0]);
	blobs[1].Definir_limites_separation(hsv_L_hand[1]);
	vector <cv::Point2f> liste = Update_blobs();
	if(liste.size() > 0){L_hand = liste[0];}
}

// Chercher la main droite
void Body::Detecter_main_droite(){
	blobs[0].Definir_limites_separation(hsv_R_hand[0]);
	blobs[1].Definir_limites_separation(hsv_R_hand[1]);
	vector <cv::Point2f> liste = Update_blobs();
	if(liste.size() > 0){R_hand = liste[0];}
}

// Chercher le pied gauche
void Body::Detecter_pied_gauche(){
	blobs[0].Definir_limites_separation(hsv_L_foot[0]);
	blobs[1].Definir_limites_separation(hsv_L_foot[1]);
	vector <cv::Point2f> liste = Update_blobs();
	if(liste.size() > 0){L_foot = liste[0];}
}

// Chercher le pied droit
void Body::Detecter_pied_droit(){
	blobs[0].Definir_limites_separation(hsv_R_foot[0]);
	blobs[1].Definir_limites_separation(hsv_R_foot[1]);
	vector <cv::Point2f> liste = Update_blobs();
	if(liste.size() > 0){R_foot = liste[0];}
}

// Getters et Setters
void Body::Set_img(cv::Mat img){this->img = img;}
cv::Point2f Body::Get_Head(){return Tete;}
cv::Point2f Body::Get_L_shoulder(){return L_shoulder;}
cv::Point2f Body::Get_R_shoulder(){return R_shoulder;}
cv::Point2f Body::Get_L_elbow(){return L_elbow;}
cv::Point2f Body::Get_R_elbow(){return R_elbow;}
cv::Point2f Body::Get_L_hand(){return L_hand;}
cv::Point2f Body::Get_R_hand(){return R_hand;}
cv::Point2f Body::Get_L_foot(){return L_foot;}
cv::Point2f Body::Get_R_foot(){return R_foot;}
void Body::Set_size(int width, int height){
	this->width = width;
	this->height = height;
	reco.Set_size(width, height);
}
