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
	NAO_flux(const int resolution, const int delais);
	NAO_flux(	const char* ip,		// adresse IP du NAO ("127.0.0.1" pour caméras locales)
			const int resolution,	// 0 : QQVGA (160*120) | 1 : QVGA (320*240) | 2 : VGA (640*480) | 3 : 4VGA (1280*960)
			const int delais,	// delais entre deux images
			const int code_couleur,	// changement espace couleurs
			const int lissage,	// flou de force lissage
			const int flip);	// miroir (0 : aucun | 1 : selon x | 2 : selon y | 3 : selon x et y)

	void Update();			// mettre à jour les images
	char Get_key() const;		// getter sur la clé
	cv::Mat Get_cam_top() const;	// getter sur image caméra supérieure
	cv::Mat Get_cam_down() const;	// getter sur image caméra inférieure
	cv::Mat Get_prev_top() const;	// getter sur image N-1 supérieure
	cv::Mat Get_prev_down() const;	// getter sur image N-1 inférieure
	cv::Mat Get_next_top() const;	// getter sur image N supérieure
	cv::Mat Get_next_down() const;	// getter sur image N inférieure

private:

	char key;			// clé de contrôle d'exécution
	int code_couleur;		// changement espace couleurs
	int delais;			// temps d'attente entre deux images (en millisecondes)
	int lissage;			// force du flou de lissage
	int flip;			// miroir
	cv::Size flou_kern;		// flou de force lissage
	cv::Mat img_cam_top;		// image caméra supérieure
	cv::Mat img_cam_down;		// image caméra inférieure
	cv::Mat img_prev_top;		// image N-1 supérieure
	cv::Mat img_prev_down;		// image N-1 inférieure
	cv::Mat img_next_top;		// image N supérieure
	cv::Mat img_next_down;		// image N inférieure

	AL::ALVideoDeviceProxy camProxy;
	std::string clientName;

	void Init(const int num_device, const int delais);
	void Init(const char* ip, const int num_device, const int delais, const int code_couleur, const int lissage, const int flip);
	void Attendre(const int millis);
	void Sauvegarder();
	void Recuperer();

};

#endif
