#ifndef SHIP_HPP
#define	SHIP_HPP

#include "constants.hpp"

class Game;

class Ship
{
    protected:
		Game * game;
        int x, y;
        int xVel, yVel;
		SDL_Surface * spriteShip;
		bool toRemove;
    public:
        Ship(Game * _game, SDL_Surface * _screen);
        virtual ~Ship();
        bool init(int _x, int _y);
        virtual void show(SDL_Surface * screen) = 0;
        virtual int getH() = 0;
        virtual int getW() = 0;
        bool getRemove();
        void setRemove(bool _toRemove);
        int getX();
        int getY();
 };

#endif	/* SHIP_HPP */
