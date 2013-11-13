CC = g++
CFLAGS = -O2 -Wall
IMP_OPENCV = `pkg-config --cflags --libs opencv`

all: main.o
	$(CC) $(CFLAGS) main.o Utils.o Flux_cam.o Blobs.o Gui.o Tracking.o Reco.o Transfo.o Calibrate.o -o naqahdah $(IMP_OPENCV)

main.o: main.cpp Utils.o Flux_cam.o Gui.o Blobs.o Tracking.o Reco.o Transfo.o Calibrate.o
	$(CC) $(CFLAGS) -c main.cpp -o main.o

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
