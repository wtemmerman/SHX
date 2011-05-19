#ifndef H_GAME
#define H_GAME

#include "constants.hpp"
#include "ship.hpp"
#include "bullet.hpp"
#include <vector>
#include <math.h>

class Player;
class Turret;
class BossLvl1;
class Hud;

class Game
{
    private: 
    	SDL_Surface * bg, * sPlayer, * sUntouchPlayer, * sPlayerLife, * sbulletPlayer, * sTurret, * sbulletTurret, * sBossLvl1, * sUntouchBoss;  
    	SDL_Surface * levelTest;
    	std::vector<Bullet *> bulletsEnnemys;
    	std::vector<Bullet *> bulletsPlayer;
    	std::vector<Ship *> enemys;	
    	std::vector<std::vector<int > > lvlInfos;
		int bgX, bgY, bgSpeed; 
		int nextInfo, lineBg;
    	bool end;
        void checkEnd();
        Player * player;
        Hud * hud;
    public:
    	Game();
    	~Game();
		void handle_input(SDL_Event event);
        bool init(std::string file);
    	void show(SDL_Surface * _screen);
    	Uint32 getPixel(SDL_Surface *surface, int x, int y);
    	void loadLevel(SDL_Surface * _imgLvl);
    	void createEnemies();
    	void addPlayerBullet(Bullet * _bulletPlayer);
    	void addEnemyBullet(Bullet * _bulletPlayer);
    	bool getEnd();
    	int getBgSpeed();
    	void setBgSpeed(int _speed);
    	SDL_Surface * getSbulletPlayer();
    	SDL_Surface * getSbulletEnemy();
    	SDL_Surface * getSPlayerLife();
    	Ship * getPlayer();
};
#endif

