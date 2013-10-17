CC = g++
CFLAGS = -O2 -Wall
IMP_OPENCV = `pkg-config --cflags --libs opencv`

all: main.o Flux_cam.o Gui.o
	$(CC) $(CFLAGS) main.o Flux_cam.o Gui.o -o naqahdah $(IMP_OPENCV)

main.o: main.cpp Flux_cam.o Gui.o
	$(CC) $(CFLAGS) -c main.cpp -o main.o

Flux_cam.o: Flux_cam.cpp
	$(CC) $(CFLAGS) -c Flux_cam.cpp -o Flux_cam.o

Gui.o: Gui.cpp
	$(CC) $(CFLAGS) -c Gui.cpp -o Gui.o

clean:
	rm -rf ./*.o
