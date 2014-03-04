/*
 * @(#)		NAO_flux.h
 * @version	1.0
 * @autor	C. Rouvière
 */

/**
 * Classe permettant d'exploiter une caméra NAO
 *	- contient les deux images précédentes enregistrées
 *	- se met à jour via la procédure "void Update()"
 *	- peut appliquer un changement d'espace de couleur (voir OpenCV doc)
 *	- peut appliquer un lissage pour les webcams de mauvaise qualité
 */

#ifndef NAO_FLUX
#define NAO_FLUX

// Aldebaran includes
#include <alproxies/alvideodeviceproxy.h>
#include <alvision/alimage.h>
#include <alvision/alvisiondefinitions.h>
#include <alerror/alerror.h>

// Opencv includes
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

// Common includes
#include <iostream>
#include <string>
#include <unistd.h>

class NAO_flux{

public:

	NAO_flux();
	~NAO_flux();
	NAO_flux(const int num_device, const int delais);
	NAO_flux(	const int resolution,	// 0 : QQVGA (160*120) | 1 : QVGA (320*240) | 2 : VGA (640*480) | 3 : 4VGA (1280*960)
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
	cv::Mat img_brute;		// image NAO
	cv::Mat img_cam;		// image webcam
	cv::Mat img_prev;		// image N-1
	cv::Mat img_next;		// image N
	cv::Mat img_show;		// image à afficher

	AL::ALVideoDeviceProxy camProxy;
	std::string clientName;

	void Init(const int num_device, const int delais);
	void Init(const int num_device, const int delais, const int code_couleur, const int lissage, const int flip);
	void Attendre(const int millis);
	void Sauvegarder();
	void Recuperer();

};

#endif
