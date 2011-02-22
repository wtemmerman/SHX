#ifndef PLAYER_HPP
#define	PLAYER_HPP

#include "constants.hpp"

class Player
{
    private:
        int x, y;
        int xVel, yVel;
		SDL_Surface * sprite;
    public:
        Player();
        ~Player();
        bool init(const char * file);
        void handle_input(SDL_Event event);
        void show(SDL_Surface *screen);
 };

#endif	/* PLAYER_HPP */
