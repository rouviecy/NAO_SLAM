CC = g++
CFLAGS = -O2 -Wall
IMP_OPENCV = `pkg-config --cflags --libs opencv`
IMP_OPENCV_LXTST = `pkg-config --cflags --libs opencv xtst`

all: calibration.o mono_control.o mono_control_click.o biblobs.o multi_control.o nao3d.o
	$(CC) $(CFLAGS) calibration.o Utils.o Flux_cam.o Gui.o Calibrate.o -o calibration $(IMP_OPENCV_LXTST)
	$(CC) $(CFLAGS) mono_control.o Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o -o mono_control $(IMP_OPENCV_LXTST)
	$(CC) $(CFLAGS) mono_control_click.o Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o -o mono_control_click $(IMP_OPENCV_LXTST)
	$(CC) $(CFLAGS) biblobs.o Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o Reco.o -o biblobs $(IMP_OPENCV_LXTST)
	$(CC) $(CFLAGS) multi_control.o Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o Transfo.o -o multi_control $(IMP_OPENCV_LXTST)
	$(CC) $(CFLAGS) nao3d.o Flux_cam.o Gui.o Body.o Reco.o Utils.o Blobs.o -o nao3d $(IMP_OPENCV_LXTST)

calibration.o: mains/calibration.cpp Utils.o Flux_cam.o Gui.o Calibrate.o
	$(CC) $(CFLAGS) -c mains/calibration.cpp -o calibration.o

mono_control.o: mains/mono_control.cpp Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o
	$(CC) $(CFLAGS) -c mains/mono_control.cpp -o mono_control.o

mono_control_click.o: mains/mono_control_click.cpp Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o
	$(CC) $(CFLAGS) -c mains/mono_control_click.cpp -o mono_control_click.o

biblobs.o: mains/biblobs.cpp Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o Reco.o
	$(CC) $(CFLAGS) -c mains/biblobs.cpp -o biblobs.o

multi_control.o: mains/multi_control.cpp Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o Transfo.o
	$(CC) $(CFLAGS) -c mains/multi_control.cpp -o multi_control.o

nao3d.o: mains/nao3d.cpp Flux_cam.o Gui.o Body.o Reco.o Utils.o Blobs.o
	$(CC) $(CFLAGS) -c mains/nao3d.cpp -o nao3d.o

Utils.o: Utils.cpp
	$(CC) $(CFLAGS) -c Utils.cpp -o Utils.o

Flux_cam.o: Flux_cam.cpp
	$(CC) $(CFLAGS) -c Flux_cam.cpp -o Flux_cam.o

Gui.o: Gui.cpp
	$(CC) $(CFLAGS) -c Gui.cpp -o Gui.o

Blobs.o: Blobs.cpp
	$(CC) $(CFLAGS) -c Blobs.cpp -o Blobs.o

Tracking.o: Tracking.cpp
	$(CC) $(CFLAGS) -c Tracking.cpp -o Tracking.o

Reco.o: Reco.cpp
	$(CC) $(CFLAGS) -c Reco.cpp -o Reco.o

Body.o: Body.cpp
	$(CC) $(CFLAGS) -c Body.cpp -o Body.o

Transfo.o: Transfo.cpp
	$(CC) $(CFLAGS) -c Transfo.cpp -o Transfo.o

Calibrate.o: Calibrate.cpp
	$(CC) $(CFLAGS) -c Calibrate.cpp -o Calibrate.o

clean:
	rm -rf ./*.o
