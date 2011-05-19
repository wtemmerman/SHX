#ifndef H_SHIP
#define	H_SHIP

#include "constants.hpp"

class Game;
class Bullet;

class Ship
{
    protected:
		Game * game;
        int x, y;
        int xVel, yVel;
        int lifes;
		SDL_Surface * spriteShip;
		bool toRemove;
    public:
        Ship(Game * _game, SDL_Surface * _screen);
        virtual ~Ship();
        bool init(int _x, int _y);
        virtual void show(SDL_Surface * screen) = 0;
        virtual void shoot()= 0;
        virtual bool collision(Bullet * _bullet) = 0;
        virtual int getH() = 0;
        virtual int getW() = 0;
		virtual int getLifes() = 0;
		virtual void setLifes(int _lifes) = 0;
        bool getRemove();
        void setRemove(bool _toRemove);
        int getX();
        int getY();
 };

#endif
