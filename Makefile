LDFLAGS = `sdl-config --cflags --libs` -lSDL_image -lSDL

all: shxv1

shxv1: main.o engine.o menu.o game.o player.o bullet.o
	g++ -o shxv1 main.o engine.o menu.o game.o player.o bullet.o $(LDFLAGS) 
	
bullet.o: bullet.cpp bullet.hpp constants.hpp 
	g++ -o bullet.o -c bullet.cpp -Wall $(LDFLAGS)	
	
player.o: player.cpp player.hpp game.hpp constants.hpp 
	g++ -o player.o -c player.cpp -Wall $(LDFLAGS)
	
game.o: game.cpp game.hpp player.hpp bullet.hpp constants.hpp 
	g++ -o game.o -c game.cpp -Wall $(LDFLAGS)
	
menu.o: menu.cpp menu.hpp engine.hpp constants.hpp 
	g++ -o menu.o -c menu.cpp -Wall $(LDFLAGS)
	
engine.o: engine.cpp engine.hpp menu.hpp game.hpp constants.hpp 
	g++ -o engine.o -c engine.cpp -Wall $(LDFLAGS)
		
main.o: main.cpp engine.hpp constants.hpp 
	g++ -o main.o -c main.cpp -Wall $(LDFLAGS)

clean:
	rm *.o

mrproper: clean
	rm shxv1
