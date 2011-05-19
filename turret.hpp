#ifndef H_TURRET
#define	H_TURRET

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
        void shoot();
        int getH();
        int getW();
        int getLifes();
		void setLifes(int _lifes);
 };

#endif	

