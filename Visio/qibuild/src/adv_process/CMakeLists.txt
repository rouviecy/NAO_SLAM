##
# Copyright (C) 2010 Aldebaran Robotics

cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)
project(adv_process)

# Ajouter la framework qibuild
find_package(qibuild)

# Créer des librairies personnalisées
qi_create_lib(IMG_PROCESS
	./src/NAO_flux.cpp
	./src/NAO_flux.h
)
qi_stage_lib(IMG_PROCESS)


# Définir les exécutables
qi_create_bin(main ./src/mains/main.cpp)

# Lier les librairies aux exécutables
qi_use_lib(main IMG_PROCESS ALCOMMON ALVISION OPENCV2_CORE OPENCV2_IMGPROC)

# Liste des librairies OPENCV pour NAO : (ne pas oublier les #include <opencv2/XXX/XXX.hpp>)
# -----> OPENCV2_CORE (structures basiques)
# -----> OPENCV2_HIGHGUI (gui et io)
# -----> OPENCV2_IMGPROC (processing)
# -----> OPENCV2_VIDEO (flot optique, ...)
# -----> OPENCV2_CALIB3D (calibration, stereo, ...)
# -----> OPENCV2_FEATURES2D (détection d'amers, appariement, ...)
# -----> OPENCV2_ML (machine learning)
# -----> OPENCV2_FLANN (???)
# -----> OPENCV2_OBJECTDETECTION (Cascade, Haar, ...)