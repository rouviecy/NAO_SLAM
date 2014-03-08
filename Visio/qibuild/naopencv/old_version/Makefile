CC = g++
CFLAGS = -O2 -Wall
IMP_OPENCV = `pkg-config --cflags --libs opencv`
IMP_OPENCV_LXTST = `pkg-config --cflags --libs opencv xtst x11`

all: calibration.o mono_control.o mono_control_click.o biblobs.o multi_control.o nao3d.o flot_optique.o
	$(CC) $(CFLAGS) calibration.o Utils.o Flux_cam.o Gui.o Calibrate.o -o ./bin/calibration $(IMP_OPENCV_LXTST)
	$(CC) $(CFLAGS) mono_control.o Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o -o ./bin/mono_control $(IMP_OPENCV_LXTST)
	$(CC) $(CFLAGS) mono_control_click.o Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o -o ./bin/mono_control_click $(IMP_OPENCV_LXTST)
	$(CC) $(CFLAGS) biblobs.o Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o Reco.o -o ./bin/biblobs $(IMP_OPENCV_LXTST)
	$(CC) $(CFLAGS) multi_control.o Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o Transfo.o -o ./bin/multi_control $(IMP_OPENCV_LXTST)
	$(CC) $(CFLAGS) nao3d.o Flux_cam.o Gui.o Body.o Reco.o Utils.o Blobs.o -o ./bin/nao3d $(IMP_OPENCV_LXTST)
	$(CC) $(CFLAGS) flot_optique.o Flux_cam.o Gui.o Tracking.o Utils.o -o ./bin/flot_optique $(IMP_OPENCV_LXTST)

calibration.o: src/mains/calibration.cpp Utils.o Flux_cam.o Gui.o Calibrate.o
	$(CC) $(CFLAGS) -c src/mains/calibration.cpp -o calibration.o

mono_control.o: src/mains/mono_control.cpp Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o
	$(CC) $(CFLAGS) -c src/mains/mono_control.cpp -o mono_control.o

mono_control_click.o: src/mains/mono_control_click.cpp Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o
	$(CC) $(CFLAGS) -c src/mains/mono_control_click.cpp -o mono_control_click.o

biblobs.o: src/mains/biblobs.cpp Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o Reco.o
	$(CC) $(CFLAGS) -c src/mains/biblobs.cpp -o biblobs.o

multi_control.o: src/mains/multi_control.cpp Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o Transfo.o
	$(CC) $(CFLAGS) -c src/mains/multi_control.cpp -o multi_control.o

nao3d.o: src/mains/nao3d.cpp Flux_cam.o Gui.o Body.o Reco.o Utils.o Blobs.o
	$(CC) $(CFLAGS) -c src/mains/nao3d.cpp -o nao3d.o

flot_optique.o: src/mains/flot_optique.cpp Flux_cam.o Gui.o Tracking.o Utils.o
	$(CC) $(CFLAGS) -c src/mains/flot_optique.cpp -o flot_optique.o

Utils.o: src/Utils.cpp
	$(CC) $(CFLAGS) -c src/Utils.cpp -o Utils.o

Flux_cam.o: src/Flux_cam.cpp
	$(CC) $(CFLAGS) -c src/Flux_cam.cpp -o Flux_cam.o

Gui.o: src/Gui.cpp
	$(CC) $(CFLAGS) -c src/Gui.cpp -o Gui.o

Blobs.o: src/Blobs.cpp
	$(CC) $(CFLAGS) -c src/Blobs.cpp -o Blobs.o

Tracking.o: src/Tracking.cpp
	$(CC) $(CFLAGS) -c src/Tracking.cpp -o Tracking.o

Reco.o: src/Reco.cpp
	$(CC) $(CFLAGS) -c src/Reco.cpp -o Reco.o

Body.o: src/Body.cpp
	$(CC) $(CFLAGS) -c src/Body.cpp -o Body.o

Transfo.o: src/Transfo.cpp
	$(CC) $(CFLAGS) -c src/Transfo.cpp -o Transfo.o

Calibrate.o: src/Calibrate.cpp
	$(CC) $(CFLAGS) -c src/Calibrate.cpp -o Calibrate.o

clean:
	rm -rf ./*.o
