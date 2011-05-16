# SHX makefile - wtx 2011

LDFLAGS = `sdl-config --cflags --libs` -lSDL_image -lSDL
CXXFLAGS = -g -Wall

OBJECTS = main.o engine.o menu.o game.o ship.o player.o turret.o bullet.o 
TARGET = shxv1

# $@ contient le nom de la cible
# $< le nom de la premiere source
# $^ le nom de toutes les sources

%.o: %.cpp
	g++	$(CXXFLAGS)	$(LDFLAGS)	-c	-o	$@	$<

all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ -o $(TARGET) $(OBJECTS) $(LDFLAGS)

clean:
	rm *.o

mrproper: clean
	rm shxv1
