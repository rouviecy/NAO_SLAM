##
# Copyright (C) 2010 Aldebaran Robotics

cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)
project(naopencv)

# Ajouter la framework qibuild
find_package(qibuild)

# Créer des librairies personnalisées
qi_create_lib(IMG_PROCESS
	./src/NAO/NAO_flux.h		./src/NAO/NAO_flux.cpp
	./src/images/Blobs.h		./src/images/Blobs.cpp
	./src/images/Calibrate.h	./src/images/Calibrate.cpp
	./src/images/Body.h		./src/images/Body.cpp
	./src/images/Reco.h		./src/images/Reco.cpp
	./src/images/Tracking.h		./src/images/Tracking.cpp
	./src/images/Transfo.h		./src/images/Transfo.cpp
	./src/images/Utils.h		./src/images/Utils.cpp
	./src/images/struct_HSV_bound.h
	./src/images/struct_wrap_bound.h
)
qi_stage_lib(IMG_PROCESS)

qi_create_lib(NAO_CONTROL
	./src/NAO/Head.h		./src/NAO/Head.cpp
	./src/NAO/Move.h		./src/NAO/Move.cpp
	./src/NAO/Leds.h		./src/NAO/Leds.cpp
	./src/NAO/Speak.h		./src/NAO/Speak.cpp
)
qi_stage_lib(NAO_CONTROL)

# Définir les exécutables
qi_create_bin(test ./src/test.cpp)
qi_create_bin(nao3d ./src/nao3d.cpp)
qi_create_bin(tracker ./src/tracker.cpp)

# Lier les librairies aux exécutables
qi_use_lib(test IMG_PROCESS ALCOMMON ALVISION OPENCV2_CORE OPENCV2_IMGPROC OPENCV2_CALIB3D OPENCV2_VIDEO)
qi_use_lib(nao3d IMG_PROCESS ALCOMMON ALVISION OPENCV2_CORE OPENCV2_IMGPROC OPENCV2_CALIB3D OPENCV2_VIDEO)
qi_use_lib(tracker IMG_PROCESS NAO_CONTROL ALCOMMON ALVISION OPENCV2_CORE OPENCV2_IMGPROC OPENCV2_CALIB3D OPENCV2_VIDEO)

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