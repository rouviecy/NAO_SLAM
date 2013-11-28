#include "Body.h"

using namespace std;

// Constructeur - Destructeur
Body::Body(){
	reco =	Reco();
	hsv_jaune =	(STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	hsv_vert =	(STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	hsv_rouge =	(STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	hsv_bleu =	(STRUCT_HSV_BOUND*) malloc(sizeof(STRUCT_HSV_BOUND));
	Couleurs();
	Membres();
}

Body::~Body(){
	free(hsv_jaune); free(hsv_vert); free(hsv_rouge); free(hsv_bleu);
}

// Paramètres colorimétriques
void Body::Couleurs(){
	hsv_jaune->H_min = 83;	hsv_jaune->S_min = 107;	hsv_jaune->V_min = 142;	hsv_jaune->seuil = 50;
	hsv_jaune->H_max = 93;	hsv_jaune->S_max = 255;	hsv_jaune->V_max = 255;
	hsv_vert->H_min = 58;	hsv_vert->S_min = 98;	hsv_vert->V_min = 84;	hsv_vert->seuil = 50;
	hsv_vert->H_max = 69;	hsv_vert->S_max = 255;	hsv_vert->V_max = 255;
	hsv_rouge->H_min = 114;	hsv_rouge->S_min = 63;	hsv_rouge->V_min = 39;	hsv_rouge->seuil = 50;
	hsv_rouge->H_max = 126;	hsv_rouge->S_max = 165;	hsv_rouge->V_max = 255;
	hsv_bleu->H_min = 2;	hsv_bleu->S_min = 36;	hsv_bleu->V_min = 46;	hsv_bleu->seuil = 50;
	hsv_bleu->H_max = 16;	hsv_bleu->S_max = 255;	hsv_bleu->V_max = 255;
}

// Couleurs des membres
void Body::Membres(){
	hsv1_L_hand = hsv_bleu;		hsv2_L_hand = hsv_rouge;
	hsv1_R_hand = hsv_bleu;		hsv2_R_hand = hsv_jaune;
	hsv1_L_foot = hsv_rouge;	hsv2_L_foot = hsv_jaune;
	hsv1_R_foot = hsv_rouge;	hsv2_R_foot = hsv_vert;
}

void Detecter_main_gauche(){

}

// Getters et Setters
void Body::Set_img(cv::Mat img){this->img = img;}
