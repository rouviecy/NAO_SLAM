CC = g++
CFLAGS = -O2 -Wall
IMP_OPENCV = `pkg-config --cflags --libs opencv`

all: calibration.o mono_control.o multi_control.o
	$(CC) $(CFLAGS) calibration.o Utils.o Flux_cam.o Gui.o Calibrate.o -o calibration $(IMP_OPENCV)
	$(CC) $(CFLAGS) mono_control.o Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o -o mono_control $(IMP_OPENCV)
	$(CC) $(CFLAGS) multi_control.o Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o Transfo.o -o multi_control $(IMP_OPENCV)

calibration.o: mains/calibration.cpp Utils.o Flux_cam.o Gui.o Calibrate.o
	$(CC) $(CFLAGS) -c mains/calibration.cpp -o calibration.o

mono_control.o: mains/mono_control.cpp Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o
	$(CC) $(CFLAGS) -c mains/mono_control.cpp -o mono_control.o

multi_control.o: mains/multi_control.cpp Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o Transfo.o
	$(CC) $(CFLAGS) -c mains/multi_control.cpp -o multi_control.o

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

Transfo.o: Transfo.cpp
	$(CC) $(CFLAGS) -c Transfo.cpp -o Transfo.o

Calibrate.o: Calibrate.cpp
	$(CC) $(CFLAGS) -c Calibrate.cpp -o Calibrate.o

clean:
	rm -rf ./*.o
