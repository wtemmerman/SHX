#ifndef H_GAME
#define H_GAME

#include "constants.hpp"
#include "ship.hpp"
#include "bullet.hpp"
#include <vector>
#include <math.h>

class Player;
class Turret;

class Game
{
    private: 
    	SDL_Surface * bg, * sPlayer, * sbulletPlayer, * sTurret, * sbulletTurret;  
    	std::vector<Bullet *> bulletsEnnemys;
    	std::vector<Bullet *> bulletsPlayer;
    	std::vector<Ship *> enemys;	
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
    	void fireBullet(int _type, int _x, int _y);
    	bool Collision(Ship * _ship, Bullet * _bullet);
};
#endif

