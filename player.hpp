#ifndef PLAYER_HPP
#define	PLAYER_HPP

#include "constants.hpp"
#include "ship.hpp"

class Game;

class Player : public Ship
{
    private:
        int previousTime;
    public:
        Player(Game * _game, SDL_Surface * _spriteShip);
        virtual ~Player();
        void handle_input(SDL_Event event);
        void show(SDL_Surface * screen);
        int getH();
        int getW();
 };

#endif	/* PLAYER_HPP */
