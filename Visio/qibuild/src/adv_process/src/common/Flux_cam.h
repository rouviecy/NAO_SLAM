/*
 * @(#)		Flux_cam.h
 * @version	1.3
 * @autor	C. Rouvière
 */

/**
 * Classe permettant d'exploiter un périphérique vidéo
 *	- contient les deux images précédentes enregistrées
 *	- se met à jour via la procédure "void Update()"
 *	- peut appliquer un changement d'espace de couleur (voir OpenCV doc)
 *	- peut appliquer un lissage pour les webcams de mauvaise qualité
 * ATTENTION : incompatible NAO !
 */

#ifndef FLUX_CAM
#define FLUX_CAM

#include <opencv/cv.h>
#include <opencv/highgui.h>

class Flux_cam{

public:

	Flux_cam();
	Flux_cam(const int num_device, const int delais);
	Flux_cam(	const int num_device,	// /dev/video[X]
			const int delais,	// delais entre deux images
			const int code_couleur,	// changement espace couleurs
			const int lissage,	// flou de force lissage
			const int flip);	// miroir (0 : aucun | 1 : selon x | 2 : selon y | 3 : selon x et y)

	void Update();			// mettre à jour les images
	char Get_key() const;		// getter sur la clé
	cv::Mat Get_cam() const;	// getter sur image webcam
	cv::Mat Get_prev() const;	// getter sur image N-1
	cv::Mat Get_next() const;	// getter sur image N

private:

	char key;			// clé de contrôle d'exécution
	int code_couleur;		// changement espace couleurs
	int delais;			// temps d'attente entre deux images (en millisecondes)
	int lissage;			// force du flou de lissage
	int flip;			// miroir
	cv::Size flou_kern;		// flou de force lissage
	cv::VideoCapture capture;	// périphérique de capture d'images
	cv::Mat img_cam;		// image webcam
	cv::Mat img_prev;		// image N-1
	cv::Mat img_next;		// image N
	cv::Mat img_show;		// image à afficher

	void Init(const int num_device, const int delais);
	void Init(const int num_device, const int delais, const int code_couleur, const int lissage, const int flip);
	void Attendre(const int millis);
	void Sauvegarder();
	void Recuperer();

};

#endif
