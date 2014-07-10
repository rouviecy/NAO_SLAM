cmake_minimum_required(VERSION 2.8)
project(NAO_SLAM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(PkgConfig)

find_package(OpenCV REQUIRED)
pkg_check_modules(X11 REQUIRED x11)
pkg_check_modules(XTST REQUIRED xtst)

set(LIBS
	${XTST_LIBRARIES}
	${X11_LIBRARIES}
)
link_libraries(${LIBS})

set(LIB_PATHS
	${XTST_LIBRARY_DIRS}
	${X11_LIBRARY_DIRS}
)
link_directories(${LIB_PATHS})

set(INCLUDE_PATHS
	${XTST_INCLUDE_DIRS}
	${X11_INCLUDE_DIRS}
)
include_directories(${INCLUDE_PATHS})

add_library(MYLIBS
	src/Blobs.h		src/Blobs.cpp
	src/Body.h		src/Body.cpp
	src/Calibrate.h		src/Calibrate.cpp
	src/Flux_cam.h		src/Flux_cam.cpp
	src/Gui.h		src/Gui.cpp
	src/Instruments.h	src/Instruments.cpp
	src/Reco.h		src/Reco.cpp
	src/Tracking.h		src/Tracking.cpp
	src/Transfo.h		src/Transfo.cpp
	src/Utils.h		src/Utils.cpp
	src/struct_HSV_bound.h
	src/struct_wrap_bound.h
)

# Projet Minority-Report
add_executable(mono_control src/mains/minority-report/mono_control.cpp)
add_executable(mono_control_click src/mains/minority-report/mono_control_click.cpp)
add_executable(multi_control src/mains/minority-report/multi_control.cpp)
target_link_libraries(mono_control ${OpenCV_LIBS} ${LIBS} MYLIBS)
target_link_libraries(mono_control_click ${OpenCV_LIBS} ${LIBS} MYLIBS)
target_link_libraries(multi_control ${OpenCV_LIBS} ${LIBS} MYLIBS)

# Projet NAOSLAM
add_executable(biblobs src/mains/nao/biblobs.cpp)
add_executable(nao3d src/mains/nao/nao3d.cpp)
add_executable(nao_pseudo3d src/mains/nao/nao_pseudo3d.cpp)
add_executable(nao_pseudo3d_and_tracking src/mains/nao/nao_pseudo3d_and_tracking.cpp)
add_executable(nao_pseudo3d_equi src/mains/nao/nao_pseudo3d_equi.cpp)
add_executable(test_HSV src/mains/nao/test_HSV.cpp)
target_link_libraries(biblobs ${OpenCV_LIBS} MYLIBS)
target_link_libraries(nao3d ${OpenCV_LIBS} MYLIBS)
target_link_libraries(nao_pseudo3d ${OpenCV_LIBS} MYLIBS)
target_link_libraries(nao_pseudo3d_and_tracking ${OpenCV_LIBS} MYLIBS)
target_link_libraries(nao_pseudo3d_equi ${OpenCV_LIBS} MYLIBS)
target_link_libraries(test_HSV ${OpenCV_LIBS} MYLIBS)

# Projet Sous-Marin
add_executable(redressement src/mains/sous-marin/redressement.cpp)
target_link_libraries(redressement ${OpenCV_LIBS} MYLIBS)

# Autres
add_executable(calibration src/mains/calibration.cpp)
add_executable(flot_optique src/mains/flot_optique.cpp)
add_executable(histogramme src/mains/histogramme.cpp)
add_executable(inertia src/mains/inertia.cpp)
add_executable(wrap src/mains/wrap.cpp)
target_link_libraries(calibration ${OpenCV_LIBS} MYLIBS)
target_link_libraries(flot_optique ${OpenCV_LIBS} MYLIBS)
target_link_libraries(histogramme ${OpenCV_LIBS} MYLIBS)
target_link_libraries(inertia ${OpenCV_LIBS} MYLIBS)
target_link_libraries(wrap ${OpenCV_LIBS} MYLIBS)