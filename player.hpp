#ifndef PLAYER_HPP
#define	PLAYER_HPP

#include "constants.hpp"
#include "ship.hpp"

class Game;

class Player : public Ship
{
    private:
        int previousTime;
        int lifes;
    public:
        Player(Game * _game, SDL_Surface * _spriteShip);
        virtual ~Player();
        void handle_input(SDL_Event event);
        void show(SDL_Surface * screen);
        int getH();
        int getW();
        int getLifes();
        void setLifes(int _lifes);
 };

#endif	/* PLAYER_HPP */
