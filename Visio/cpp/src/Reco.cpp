#include "Reco.h"

using namespace std;

// Constructeur
Reco::Reco(){
	blanc = cv::Scalar(255);
	bleu = cv::Scalar(255, 0, 0);
	rouge = cv::Scalar(0, 0, 255);
	cyan = cv::Scalar(255, 255, 0);
	jaune = cv::Scalar(0, 255, 255);
	int r = 5;
	cv::Mat rond = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(2*r+1, 2*r+1), cv::Point(r,r));
}

// Tests de reconnaissance de cercle
std::vector <bool> Reco::Test_circle(){
	vector <bool> result;
	for(vector <cv::Point2i> ::iterator blob = blobs_1.begin(); blob != blobs_1.end(); ++blob){
		// TODO : travailler avec blob
	}
	return result;
}

// Test de reconnaissance de blob dans un blob
std::vector <cv::Point2i> Reco::Test_inclusion(const int dist_max){
	mu.clear(), mc.clear();
	Update_mats((int) dist_max / 2);
	mat_compare = mat_blobs_1 & mat_blobs_2;
	cv::findContours(mat_compare, liste_blobs, hierarchie_blobs, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	if(hierarchie_blobs.size() <= 0){return mc;}
	for(size_t i = 0; i < liste_blobs.size(); i++){
		mu.push_back(cv::moments(liste_blobs[i], false));
		mc.push_back(cv::Point2i(mu[i].m10/mu[i].m00, mu[i].m01/mu[i].m00));
	}
	return mc;
}

// Mettre à jour les matrices des blobs
void Reco::Update_mats(const int rayon){
	mat_1 = cv::Mat::zeros(taille, CV_8U);
	mat_2 = cv::Mat::zeros(taille, CV_8U);
	for(vector <cv::Point2i> ::iterator blob = blobs_1.begin(); blob != blobs_1.end(); ++blob){
		cv::circle(mat_1, cv::Point2i((int) floor((*blob).x), (int) floor((*blob).y)), rayon, blanc, -1, 8, 0);
	}
	for(vector <cv::Point2i> ::iterator blob = blobs_2.begin(); blob != blobs_2.end(); ++blob){
		cv::circle(mat_2, cv::Point2i((int) floor((*blob).x), (int) floor((*blob).y)), rayon, blanc, -1, 8, 0);
	}
	cv::Scalar mini(42); cv::Scalar maxi(255);
	inRange(mat_1, mini, maxi, mat_blobs_1);
	inRange(mat_2, mini, maxi, mat_blobs_2);
}

// Détecter un quadrillage sur l'image dans le buffer
void Reco::Detecter_quadrillage(){
	liste_quadrillage.clear();

	// Définir la zone de travail
	int max_x = image.cols;
	int max_y = image.rows;

	// Extraire les contours
	cv::Mat image_contours;
	image.copyTo(image_quadrillage);
	cv::cvtColor(image, image, CV_RGB2GRAY, 1);
	cv::equalizeHist(image, image);
	cv::Canny(image, image_contours, 100, 255);
	cv::imshow("Canny", image_contours);

	// Trouver les lignes
	vector <cv::Vec4i> lignes;
	cv::HoughLinesP(image_contours, lignes, 1, CV_PI/90, 100, 50, 100);

	// Trouver leurs intersections
	std::vector <cv::Point2f> intersections, coins;
	for(size_t i = 0; i < lignes.size(); i++){
//		cv::line(image_quadrillage, cv::Point(lignes[i][0], lignes[i][1]), cv::Point(lignes[i][2], lignes[i][3]), bleu);
		for(size_t j = i + 1; j < lignes.size(); j++){
			cv::Point2f pt = Intersection(lignes[i], lignes[j], 3);
			if(!Utils::In_img(pt, max_x, max_y)){continue;}
			intersections.push_back(pt);
		}
	}

	// Fusionnner les intersections proches
	cv::Subdiv2D subdiv(cv::Rect(0, 0, max_x, max_y));
	for(size_t i = 0; i < intersections.size(); i++){
		if(!Utils::In_img(intersections[i], max_x, max_y)){continue;}
		int compteur = 1;
		cv::Point2f somme = intersections[i];
		for(size_t j = i + 1; j < intersections.size(); j++){
			if(!Utils::In_img(intersections[j], max_x, max_y)){continue;}
			float dx = intersections[i].x - intersections[j].x;
			float dy = intersections[i].y - intersections[j].y;
			float distance = dx * dx + dy * dy;
			if(distance < 800){
				compteur++;
				somme += intersections[j];
				intersections[j] = cv::Point2f(-1, -1);
			}
		}
		cv::Point2f barycentre = (float) (1. / compteur) * somme;
		if(!Utils::In_img(barycentre, max_x, max_y)){continue;}
		coins.push_back(barycentre);
		cv::circle(image_quadrillage, barycentre, 3, rouge, 2);
	}

	// Triangulation de Delaunay
	subdiv.insert(coins);
	vector <int> edges = Liste_edges_int(subdiv, max_x, max_y, image_quadrillage);
	for(size_t i = 0; i < edges.size(); i++){
		int e = edges[i];
		cv::Point2f B, D;
		subdiv.edgeOrg(e, &B);
		subdiv.edgeDst(e, &D);
		if(!Utils::In_img(B, max_x, max_y) || !Utils::In_img(D, max_x, max_y)){continue;}
//		cv::line(image_quadrillage, B, D, cyan);
		int e_nl = subdiv.getEdge(e, cv::Subdiv2D::NEXT_AROUND_LEFT);
		int e_nr = subdiv.getEdge(e, cv::Subdiv2D::NEXT_AROUND_RIGHT);
		cv::Point2f A, C;
		subdiv.edgeDst(e_nl, &A);
		subdiv.edgeOrg(e_nr, &C);
		if(!Utils::In_img(A, max_x, max_y) || !Utils::In_img(C, max_x, max_y)){continue;}
		cv::Vec4i segment[4] = {
			cv::Vec4i(A.x, A.y, B.x, B.y),
			cv::Vec4i(B.x, B.y, C.x, C.y),
			cv::Vec4i(C.x, C.y, D.x, D.y),
			cv::Vec4i(D.x, D.y, A.x, A.y)
		};
		bool ok = true;
		for(int j = 0; ok && j < 4; j++){
			ok = false;
			for(size_t k = 0; k < lignes.size(); k++){
				if(Confondus(lignes[k], segment[j])){ok = true; break;}
			}
		}
		if(!ok){continue;}
		cv::Point2f sommets[4] = {A, B, C, D};
		for(int j = 0; j < 4; j++){
			for(int k = j + 1; k < 4; k++){
				if(Utils::Distance_carree(sommets[j].x, sommets[j].y, sommets[k].x, sommets[k].y) < 2000){ok = false;}
			}
		}
		if(ok){
			cv::line(image_quadrillage, A, B, jaune);
			cv::line(image_quadrillage, B, C, jaune);
			cv::line(image_quadrillage, C, D, jaune);
			cv::line(image_quadrillage, D, A, jaune);
			vector <cv::Point2i> quadrillage;
			quadrillage.push_back(cv::Point2i(A.x, A.y));
			quadrillage.push_back(cv::Point2i(B.x, B.y));
			quadrillage.push_back(cv::Point2i(C.x, C.y));
			quadrillage.push_back(cv::Point2i(D.x, D.y)); 
			liste_quadrillage.push_back(quadrillage);
		}

	}

}

// Si deux droites sont (quasi-)confondues
bool Reco::Confondus(cv::Vec4i a, cv::Vec4i b) const{
	int xA = a[0], yA = a[1], xB = a[2], yB = a[3];
	for(int i = 0; i < 2; i++){
		float dx = (float) (xB - xA);
		float dy = (float) (yB - yA);
		float l = dx * dx + dy * dy;
		float dx_m = float (b[2*i] - xA);
		float dy_m = float (b[2*i+1] - yA);
		if(l < 42){return false;}
		float numerateur = dy * dx_m - dx * dy_m;
		float d_carre = numerateur * numerateur / l;
		if(d_carre > 500){return false;}
	}
	return true;
}

// Trouver l'intersection entre deux droites, si elles ne sont pas trop parallèles
cv::Point2f Reco::Intersection(cv::Vec4i a, cv::Vec4i b, int coeff) const{
	int x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3], x3 = b[0], y3 = b[1], x4 = b[2], y4 = b[3];
	float dx_a = (float) (x1 - x2);
	float dy_a = (float) (y1 - y2);
	float dx_b = (float) (x3 - x4);
	float dy_b = (float) (y3 - y4);
	float P = (dx_a * dy_b) - (dy_a * dx_b);
	float Q = (dx_a * dx_b) + (dy_a * dy_b);
	if(P && abs(Q) < coeff * abs(P)){
		cv::Point2f pt;
		float pr_a = (float) (x1 * y2 - y1 * x2);
		float pr_b = (float) (x3 * y4 - y3 * x4);
		pt.x = (pr_a * dx_b - pr_b * dx_a) / P;
		pt.y = (pr_a * dy_b - pr_b * dy_a) / P;
		return pt;
	}
	else{	return cv::Point2f(-1, -1);}
}

// Extraire d'une subdivision la liste des index des edges
vector <int> Reco::Liste_edges_int(cv::Subdiv2D s, int max_x, int max_y, cv::Mat image){
	std::set <int> resultat_set;
	vector <cv::Vec6f> triangles;
	s.getTriangleList(triangles);
	for(size_t i = 0; i < triangles.size(); i++){
		cv::Point2f pt1(triangles[i][0], triangles[i][1]);
		cv::Point2f pt2(triangles[i][2], triangles[i][3]);
		cv::Point2f pt3(triangles[i][4], triangles[i][5]);
		cv::Point2f bary = (1./3) * (pt1 + pt2 + pt3);
		if(!Utils::In_img(bary, max_x, max_y)){continue;}
		int e0 = 0, vertex = 0;
		s.locate(bary, e0, vertex);
		resultat_set.insert(e0);
		int e = e0;
		do{
			e = s.getEdge(e, cv::Subdiv2D::NEXT_AROUND_RIGHT);
			resultat_set.insert(e);
		}while(e != e0);

	}
	vector <int> resultat_vector;
	for(std::set<int>::iterator it = resultat_set.begin(); it != resultat_set.end(); ++it){
		resultat_vector.push_back(*it);
	}
	return resultat_vector;
}

// Getters et Setters
cv::Mat Reco::Get_img_quadrillage() const{return this->image_quadrillage;}
vector < vector <cv::Point2i> > Reco::Get_quadrillage() const{return this->liste_quadrillage;}
void Reco::Set_img(cv::Mat image){image.copyTo(this->image);}
void Reco::Set_blobs_1(vector <cv::Point2i> blobs_1){this->blobs_1 = blobs_1;}
void Reco::Set_blobs_2(vector <cv::Point2i> blobs_2){this->blobs_2 = blobs_2;}
void Reco::Set_size(cv::Size taille){this->taille = taille;}
