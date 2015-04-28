/*
 * @(#)		IO_file.h
 * @version	1.1
 * @autor	C. Rouvière
 */

/**
 * Classe de lecture et écriture d'images
 */

#ifndef IO_FILE
#define IO_FILE

#include "struct_nom.h"

#include <opencv2/opencv.hpp>

#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <string>
#include <stdio.h>
#include <dirent.h>

class IO_file{

public:

	IO_file();

	std::vector <STRUCT_NOM> Lister_fichiers(const std::string path);	// Récupérer la liste des fichiers avec et sans chemin complet
	std::vector <STRUCT_NOM> Lister_fichiers(
		const std::string path,
		const std::string ext);						// Filtrer extension

	cv::Mat Extraire_image(const std::string nom_complet);			// Lire une image dans un fichier
	void Ecrire_image(							// Écrire une image dans un fichier
		const cv::Mat image,						// Image à écrire
		const std::string nom_complet);					// Chemin complet de la cible
	void Ecrire_rectangles(							// Écrire le log des rectangles détectés
		const std::vector <cv::Rect> rectangles,			// Liste des rectangles
		const std::string nom_complet);					// Chemin complet de la cible
	std::vector <cv::Rect> Lire_rectangles(const std::string nom_complet);	// Lire la liste des rectangles d'un fichier

private:

};

#endif
