#ifndef BULLET_HPP
#define	BULLET_HPP

#include "constants.hpp"

class Bullet
{
    private:
        int x, y;
        int xVel, yVel;
		SDL_Surface * spriteBullet;
		bool toRemove;
    public:
        Bullet();
        ~Bullet();
        bool init(SDL_Surface * spriteBullet);
        void show(SDL_Surface * screen);
        bool getRemove();
 };

#endif	/* BULLET_HPP */
