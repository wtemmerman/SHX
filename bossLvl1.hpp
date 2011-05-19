#ifndef H_BOSS1
#define	H_BOSS1

#include "constants.hpp"
#include "ship.hpp"
#include <time.h>

class Game;

class BossLvl1 : public Ship
{
    private:
        int previousTime;
        int futurPos;
    public:
        BossLvl1(Game * _game, SDL_Surface * _spriteShip);
        virtual ~BossLvl1();
        void show(SDL_Surface * screen);
        void shoot();
        bool collision(Bullet * _bullet);
        int getH();
        int getW();
        int getLifes();
		void setLifes(int _lifes);
 };

#endif	
