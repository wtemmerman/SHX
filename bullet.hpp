#ifndef H_BULLET
#define	H_BULLET

#include "constants.hpp"
#include "ship.hpp"
#include <math.h>


class Bullet
{
    private:
        double x, y; 
        double xVel, yVel;
        double angle, length;
		SDL_Surface * spriteBullet;
		bool toRemove;
		int type;
    public:
        Bullet(SDL_Surface * _spriteBullet);
        ~Bullet();
        bool init(int _x, int _y, double _angle, double _length);
        void show(SDL_Surface * screen);
        bool getRemove();
        int getX();
        int getY();
        int getW();
        int getH();
 };

#endif	
