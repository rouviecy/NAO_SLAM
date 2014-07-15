#include "IO_file.h"

using namespace std;

// Constructeur
IO_file::IO_file(){}

vector <STRUCT_NOM> IO_file::Lister_fichiers(const string path){return Lister_fichiers(path, "");}
vector <STRUCT_NOM> IO_file::Lister_fichiers(const string path, const string ext){
	vector <STRUCT_NOM> liste_path;
	DIR* dossier = opendir(path.c_str());
	if(dossier == NULL){
		cerr << "Erreur : adresse de lecture invalide" << endl;
		throw exception();
	}
	struct dirent * ent;
	while((ent = readdir(dossier)) != NULL){
		if(strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")){
			STRUCT_NOM nouveau;
			nouveau.nom = ent->d_name;
			nouveau.nom_complet = path + "/" + ent->d_name;
			nouveau.extension = nouveau.nom.substr(nouveau.nom.rfind('.') + 1);
			if(strcmp(nouveau.extension.c_str(), ext.c_str()) != 0 && !ext.empty()){continue;}
			liste_path.push_back(nouveau);
		}
	}
	closedir(dossier);
	return liste_path;
}

cv::Mat IO_file::Extraire_image(const string nom_complet){
	try{return cv::imread(nom_complet);}
	catch(cv::Exception& e){
		cerr << "Erreur : lecture image impossible" << e.what() << endl;
		cv::Mat image;
		return image;
	}
}

void IO_file::Ecrire_image(const cv::Mat image, const string nom_complet){
	try{cv::imwrite(nom_complet, image);}
	catch(cv::Exception& e){cerr << "Erreur : écriture image impossible" << e.what() << endl;}
}

void IO_file::Ecrire_rectangles(const vector <cv::Rect> rectangles, const string nom_complet){
	ofstream fichier;
	fichier.open(nom_complet.c_str());
	for(size_t i = 0; i < rectangles.size(); i++){
		cv::Rect r = rectangles[i];
		fichier << r.x << " " << r.y << " " << r.width << " " << r.height << "\n";
	}
	fichier.close();
}

vector <cv::Rect> IO_file::Lire_rectangles(const string nom_complet){
	vector <cv::Rect> rectangles;
	ifstream fichier(nom_complet.c_str());
	string ligne, element;
	int i, x, y, w, h;
	while(getline(fichier, ligne)){
		i = 0;
		stringstream ss(ligne);
		while(getline(ss, element, ' ')){
			if	(i == 0){x = stoi(element);}
			else if	(i == 1){y = stoi(element);}
			else if	(i == 2){w = stoi(element);}
			else if	(i == 3){h = stoi(element);}
			i++;
		}
		if(i != 4){cerr << "Erreur : fichier liste floutages corrompu" << endl;}
		else{rectangles.push_back(cv::Rect(x, y, w, h));}
	}
	return rectangles;
}
