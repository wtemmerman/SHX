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
		SDL_Surface * spritePlayer;
    public:
        Player(Game * _game);
        ~Player();
        bool init(const char * file);
        void handle_input(SDL_Event event);
        void show(SDL_Surface * screen);
        int getX();
        int getY();
 };

#endif	/* PLAYER_HPP */
