#ifndef H_GAME
#define H_GAME

#include "constants.hpp"
#include "player.hpp"

class Game
{
    private: 
    	SDL_Surface *bg;
		int bgX, bgY; 
    	bool end;
        void checkEnd();
        Player * player;
    public:
    	Game();
    	~Game();
	
		void handle_input(SDL_Event event);
        bool init(std::string file);
    	void show(SDL_Surface *screen);
    	bool getEnd();
};
#endif

