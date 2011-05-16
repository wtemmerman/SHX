#ifndef SHIP_HPP
#define	SHIP_HPP

#include "constants.hpp"
#include "game.hpp"

class Game;

class Ship
{
    protected:
		Game * game;
        int x, y;
        int xVel, yVel;
		SDL_Surface * spriteShip;
		
    public:
        Ship(Game * _game);
        virtual ~Ship();
        bool init(const char * file, int _x, int _y);
        virtual void show(SDL_Surface * screen) = 0;
        int getX();
        int getY();
 };

#endif	/* SHIP_HPP */
