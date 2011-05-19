#ifndef H_PLAYER
#define	H_PLAYER

#include "constants.hpp"
#include "ship.hpp"

class Game;

class Player : public Ship
{
    private:

    public:
        Player(Game * _game, SDL_Surface * _spriteShip, SDL_Surface * _spriteUntouch);
        ~Player();
        void handle_input(SDL_Event event);
        void show(SDL_Surface * screen);
        void shoot();
        bool collision(Bullet * _bullet);
        int getH();
        int getW();
        int getLifes();
        void setLifes(int _lifes);

 };

#endif	
