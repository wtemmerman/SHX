#ifndef PLAYER_HPP
#define	PLAYER_HPP

#include "constants.hpp"
#include "game.hpp"

class Game;

class Player
{
    private:
		Game * game;
        int x, y;
        int xVel, yVel;
		SDL_Surface * sprite;
    public:
        Player(Game * game);
        ~Player();
        bool init(const char * file);
        void handle_input(SDL_Event event);
        void show(SDL_Surface * screen);
 };

#endif	/* PLAYER_HPP */
