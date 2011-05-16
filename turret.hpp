#ifndef TURRET_HPP
#define	TURRET_HPP

#include "constants.hpp"
#include "ship.hpp"

class Game;

class Turret : public Ship
{
    private:
        int previousTime;
    public:
        Turret(Game * _game, SDL_Surface * _spriteShip);
        virtual ~Turret();
        void show(SDL_Surface * screen);
        int getH();
        int getW();
 };

#endif	/* TURRET_HPP */

