#ifndef PLAYER_HPP
#define	PLAYER_HPP

#include "constants.hpp"
#include "ship.hpp"

class Game;

class Player : public Ship
{
    private:
        unsigned int previousTime;
    public:
        Player(Game * _game);
        virtual ~Player();
        void handle_input(SDL_Event event);
        void show(SDL_Surface * screen);
 };

#endif	/* PLAYER_HPP */
