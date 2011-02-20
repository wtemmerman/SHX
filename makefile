LDFLAGS = `sdl-config --cflags --libs` -lSDL_image -lSDL

all: shxv1

shxv1: main.o moteur.o menu.o jeu.o
	g++ -o shxv1 main.o moteur.o menu.o jeu.o $(LDFLAGS) 
	
jeu.o: jeu.cpp jeu.hpp constants.hpp 
	g++ -o jeu.o -c jeu.cpp -Wall $(LDFLAGS)
	
menu.o: menu.cpp menu.hpp moteur.hpp constants.hpp 
	g++ -o menu.o -c menu.cpp -Wall $(LDFLAGS)
	
moteur.o: moteur.cpp moteur.hpp menu.hpp jeu.hpp constants.hpp 
	g++ -o moteur.o -c moteur.cpp -Wall $(LDFLAGS)
		
main.o: main.cpp moteur.hpp constants.hpp 
	g++ -o main.o -c main.cpp -Wall $(LDFLAGS)

clean:
	rm *.o

mrproper: clean
	rm shxv1
