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
        Turret(Game * _game, SDL_Surface * _spriteShip, SDL_Surface * _spriteUntouch);
        virtual ~Turret();
        void show(SDL_Surface * screen);
        void shoot();
        bool collision(Bullet * _bullet);
        int getH();
        int getW();
        int getLifes();
		void setLifes(int _lifes);
 };

#endif	

