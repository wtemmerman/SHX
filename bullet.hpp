#ifndef BULLET_HPP
#define	BULLET_HPP

#include "constants.hpp"
#include "ship.hpp"
#include <math.h>


class Bullet
{
    private:
        int x, y;
        double angle, length;
		SDL_Surface * spriteBullet;
		bool toRemove;
		int type;
    public:
        Bullet();
        ~Bullet();
        bool init(SDL_Surface * _spriteBullet, int _x, int _y, double _angle, double _length,int _type);
        void show(SDL_Surface * screen);
        bool getRemove();
        bool collision(Ship * _ship);
        int getX();
        int getY();
        int getW();
        int getH();
 };

#endif	/* BULLET_HPP */
