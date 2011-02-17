LDFLAGS = `sdl-config --cflags --libs` -lSDL_image -lSDL

all: shxv1

shxv1: main.o Game.o Player.o 
	g++ -o shxv1 main.o Game.o Player.o $(LDFLAGS) 

Player.o: Player.cpp Player.hpp Constants.hpp
	g++ -o Player.o -c Player.cpp -Wall $(LDFLAGS)
	
Game.o: Game.cpp Game.hpp Player.hpp Constants.hpp 
	g++ -o Game.o -c Game.cpp -Wall $(LDFLAGS)
	
main.o: main.cpp Game.hpp Constants.hpp 
	g++ -o main.o -c main.cpp -Wall $(LDFLAGS)

clean:
	rm *.o

mrproper: clean
	rm shxv1
