#ifndef H_GAME
#define H_GAME

#include "constants.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include <vector>

class Player;

class Game
{
    private: 
    	SDL_Surface * bg;
    	SDL_Surface * bullet;  
    	std::vector<Bullet> bulletsPlayer;
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
    	void fireBullet();
    	SDL_Surface * getBulletSurface();
};
#endif

