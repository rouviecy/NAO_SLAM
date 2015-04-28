#include "Body.h"

using namespace std;

// Constructeur - Destructeur
Body::Body(){
	hsv_jaune =	(hsv_params*) malloc(sizeof(hsv_params));
	hsv_vert =	(hsv_params*) malloc(sizeof(hsv_params));
	hsv_rose =	(hsv_params*) malloc(sizeof(hsv_params));
	hsv_lavande =	(hsv_params*) malloc(sizeof(hsv_params));
	hsv_turq =	(hsv_params*) malloc(sizeof(hsv_params));
	hsv_beige =	(hsv_params*) malloc(sizeof(hsv_params));
	hsv_pastis =	(hsv_params*) malloc(sizeof(hsv_params));
	hsv_mauve =	(hsv_params*) malloc(sizeof(hsv_params));
	blobs = new Blobs[2];
	Couleurs();
	Membres();
	Tete = cv::Point2i(0, 0);
	T_torso = cv::Point2i(0, 0);	B_torso = cv::Point2i(0, 0);
	L_shoulder = cv::Point2i(0, 0);	R_shoulder = cv::Point2i(0, 0);
	L_elbow = cv::Point2i(0, 0);	R_elbow = cv::Point2i(0, 0);
	L_hand = cv::Point2i(0, 0);	R_hand = cv::Point2i(0, 0);
	L_knee = cv::Point2i(0, 0);	R_knee = cv::Point2i(0, 0);
	L_foot = cv::Point2i(0, 0);	R_foot = cv::Point2i(0, 0);
}

Body::~Body(){
	free(hsv_jaune); free(hsv_vert); free(hsv_rose); free(hsv_lavande); free(hsv_turq); free(hsv_beige); free(hsv_pastis); free(hsv_mauve);
	delete[] blobs;
}

// Paramètres colorimétriques
void Body::Couleurs(){
	hsv_lavande->H_min = 0;	hsv_lavande->S_min = 42;hsv_lavande->V_min = 62;hsv_lavande->nb_dilate = 5;	hsv_lavande->seuil = 5;
	hsv_lavande->H_max = 12;hsv_lavande->S_max = 255;hsv_lavande->V_max = 255;hsv_lavande->nb_erode = 5;
	hsv_turq->H_min = 23;	hsv_turq->S_min = 104;	hsv_turq->V_min = 75;	hsv_turq->nb_dilate = 5;	hsv_turq->seuil = 5;
	hsv_turq->H_max = 35;	hsv_turq->S_max = 255;	hsv_turq->V_max = 255;	hsv_turq->nb_erode = 6;
	hsv_vert->H_min = 46;	hsv_vert->S_min = 88;	hsv_vert->V_min = 73;	hsv_vert->nb_dilate = 5;	hsv_vert->seuil = 5;
	hsv_vert->H_max = 51;	hsv_vert->S_max = 255;	hsv_vert->V_max = 255;	hsv_vert->nb_erode = 5;
	hsv_pastis->H_min = 68;	hsv_pastis->S_min = 143;hsv_pastis->V_min = 96;	hsv_pastis->nb_dilate = 5;	hsv_pastis->seuil = 5;
	hsv_pastis->H_max = 83;	hsv_pastis->S_max = 255;hsv_pastis->V_max = 255;hsv_pastis->nb_erode = 5;
	hsv_jaune->H_min = 93;	hsv_jaune->S_min = 91;	hsv_jaune->V_min = 127;	hsv_jaune->nb_dilate = 5;	hsv_jaune->seuil = 5;
	hsv_jaune->H_max = 103;	hsv_jaune->S_max = 255;	hsv_jaune->V_max = 255;	hsv_jaune->nb_erode = 6;
	hsv_beige->H_min = 114;	hsv_beige->S_min = 67;	hsv_beige->V_min = 75;	hsv_beige->nb_dilate = 5;	hsv_beige->seuil = 5;
	hsv_beige->H_max = 120;	hsv_beige->S_max = 255;	hsv_beige->V_max = 255;	hsv_beige->nb_erode = 5;
	hsv_rose->H_min = 128;	hsv_rose->S_min = 129;	hsv_rose->V_min = 122;	hsv_rose->nb_dilate = 5;	hsv_rose->seuil = 5;
	hsv_rose->H_max = 146;	hsv_rose->S_max = 255;	hsv_rose->V_max = 255;	hsv_rose->nb_erode = 6;
	hsv_mauve->H_min = 144;	hsv_mauve->S_min = 92;	hsv_mauve->V_min = 43;	hsv_mauve->nb_dilate = 5;	hsv_mauve->seuil = 5;
	hsv_mauve->H_max = 159;	hsv_mauve->S_max = 255;	hsv_mauve->V_max = 255;	hsv_mauve->nb_erode = 6;
}

// Couleurs des membres
void Body::Membres(){
	hsv_Tete[0] =		hsv_turq;	hsv_Tete[1] =		hsv_beige;
	hsv_T_torso[0] =	hsv_turq;	hsv_T_torso[1] =	hsv_pastis;
	hsv_B_torso[0] =	hsv_turq;	hsv_B_torso[1] =	hsv_rose;
	hsv_L_shoulder[0] =	hsv_lavande;	hsv_L_shoulder[1] =	hsv_vert;
	hsv_R_shoulder[0] =	hsv_lavande;	hsv_R_shoulder[1] =	hsv_turq;
	hsv_L_elbow[0] =	hsv_lavande;	hsv_L_elbow[1] =	hsv_pastis;
	hsv_R_elbow[0] =	hsv_lavande;	hsv_R_elbow[1] =	hsv_rose;
	hsv_L_hand[0] =		hsv_lavande;	hsv_L_hand[1] =		hsv_jaune;
	hsv_R_hand[0] =		hsv_lavande;	hsv_R_hand[1] =		hsv_mauve;
	hsv_L_knee[0] =		hsv_beige;	hsv_L_knee[1] =		hsv_pastis;
	hsv_R_knee[0] =		hsv_beige;	hsv_R_knee[1] =		hsv_rose;
	hsv_L_foot[0] =		hsv_beige;	hsv_L_foot[1] =		hsv_jaune;
	hsv_R_foot[0] =		hsv_beige;	hsv_R_foot[1] =		hsv_mauve;
}

// Mettre à jour le détecteur de blobs
vector <cv::Point2i> Body::Update_blobs(hsv_params *hsv_1, hsv_params *hsv_2){
	blobs[0].Definir_limites_separation(hsv_1);
	blobs[1].Definir_limites_separation(hsv_2);
	for(int i = 0; i < 2; i++){
		blobs[i].Set_img(img);
		blobs[i].Separer();
		blobs[i].Trouver_blobs();
	}
	reco.Set_blobs_1(blobs[0].Get_mc());
	reco.Set_blobs_2(blobs[1].Get_mc());
	reco.Set_size(img.size());
	return reco.Test_inclusion(20);
}

// Chercher la tête
void Body::Detecter_tete(){
	vector <cv::Point2i> liste = Update_blobs(hsv_Tete[0], hsv_Tete[1]);
	if(liste.size() > 0){Tete = liste[0];}
}

// Chercher le haut du torse
void Body::Detecter_torse_haut(){
	vector <cv::Point2i> liste = Update_blobs(hsv_T_torso[0], hsv_T_torso[1]);
	if(liste.size() > 0){T_torso = liste[0];}
}

// Chercher le bas du torse
void Body::Detecter_torse_bas(){
	vector <cv::Point2i> liste = Update_blobs(hsv_B_torso[0], hsv_B_torso[1]);
	if(liste.size() > 0){B_torso = liste[0];}
}

// Chercher l'épaule gauche
void Body::Detecter_epaule_gauche(){
	vector <cv::Point2i> liste = Update_blobs(hsv_L_shoulder[0], hsv_L_shoulder[1]);
	if(liste.size() > 0){L_shoulder = liste[0];}
}

// Chercher l'épaule droite
void Body::Detecter_epaule_droite(){
	vector <cv::Point2i> liste = Update_blobs(hsv_R_shoulder[0], hsv_R_shoulder[1]);
	if(liste.size() > 0){R_shoulder = liste[0];}
}

// Chercher le coude gauche
void Body::Detecter_coude_gauche(){
	vector <cv::Point2i> liste = Update_blobs(hsv_L_elbow[0], hsv_L_elbow[1]);
	if(liste.size() > 0){L_elbow = liste[0];}
}

// Chercher le coude droit
void Body::Detecter_coude_droit(){
	vector <cv::Point2i> liste = Update_blobs(hsv_R_elbow[0], hsv_R_elbow[1]);
	if(liste.size() > 0){R_elbow = liste[0];}
}

// Chercher la main gauche
void Body::Detecter_main_gauche(){
	vector <cv::Point2i> liste = Update_blobs(hsv_L_hand[0], hsv_L_hand[1]);
	if(liste.size() > 0){L_hand = liste[0];}
}

// Chercher la main droite
void Body::Detecter_main_droite(){
	vector <cv::Point2i> liste = Update_blobs(hsv_R_hand[0], hsv_R_hand[1]);
	if(liste.size() > 0){R_hand = liste[0];}
}

// Chercher le genou gauche
void Body::Detecter_genou_gauche(){
	vector <cv::Point2i> liste = Update_blobs(hsv_L_knee[0], hsv_L_knee[1]);
	if(liste.size() > 0){L_knee = liste[0];}
}

// Chercher le genou droit
void Body::Detecter_genou_droit(){
	vector <cv::Point2i> liste = Update_blobs(hsv_R_knee[0], hsv_R_knee[1]);
	if(liste.size() > 0){R_knee = liste[0];}
}

// Chercher le pied gauche
void Body::Detecter_pied_gauche(){
	vector <cv::Point2i> liste = Update_blobs(hsv_L_foot[0], hsv_L_foot[1]);
	if(liste.size() > 0){L_foot = liste[0];}
}

// Chercher le pied droit
void Body::Detecter_pied_droit(){
	vector <cv::Point2i> liste = Update_blobs(hsv_R_foot[0], hsv_R_foot[1]);
	if(liste.size() > 0){R_foot = liste[0];}
}

// Getters et Setters
void		Body::Set_img(cv::Mat img)	{this->img = img;}
cv::Point2i	Body::Get_Head()		{return Tete;}
cv::Point2i	Body::Get_T_torso()		{return T_torso;}
cv::Point2i	Body::Get_B_torso()		{return B_torso;}
cv::Point2i	Body::Get_L_shoulder()		{return L_shoulder;}
cv::Point2i	Body::Get_R_shoulder()		{return R_shoulder;}
cv::Point2i	Body::Get_L_elbow()		{return L_elbow;}
cv::Point2i	Body::Get_R_elbow()		{return R_elbow;}
cv::Point2i	Body::Get_L_hand()		{return L_hand;}
cv::Point2i	Body::Get_R_hand()		{return R_hand;}
cv::Point2i	Body::Get_L_knee()		{return L_knee;}
cv::Point2i	Body::Get_R_knee()		{return R_knee;}
cv::Point2i	Body::Get_L_foot()		{return L_foot;}
cv::Point2i	Body::Get_R_foot()		{return R_foot;}
