CC = g++
CFLAGS = -O2 -Wall
IMP_OPENCV = `pkg-config --cflags --libs opencv`

all: main.o Flux_cam.o Gui.o Blobs.o
	$(CC) $(CFLAGS) main.o Flux_cam.o Blobs.o Gui.o -o naqahdah $(IMP_OPENCV)

main.o: main.cpp Flux_cam.o Gui.o Blobs.o
	$(CC) $(CFLAGS) -c main.cpp -o main.o

Flux_cam.o: Flux_cam.cpp
	$(CC) $(CFLAGS) -c Flux_cam.cpp -o Flux_cam.o

Gui.o: Gui.cpp
	$(CC) $(CFLAGS) -c Gui.cpp -o Gui.o

Blobs.o: Blobs.cpp
	$(CC) $(CFLAGS) -c Blobs.cpp -o Blobs.o

clean:
	rm -rf ./*.o
