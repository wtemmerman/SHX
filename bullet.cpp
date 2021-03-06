 #include "bullet.hpp"
 
 using namespace std;
 
 Bullet::Bullet(SDL_Surface * _spriteBullet)
{
    x = 0.0;
    y = 0.0;
	xVel = 0.0;
	yVel = 0.0;
	
    angle = 0.0;
    length = 0.0;
   
	toRemove = false;
	
	type = 0;
	
    spriteBullet = _spriteBullet;
}

Bullet::~Bullet()
{
	if(spriteBullet != NULL)
		SDL_FreeSurface(spriteBullet);
}

bool Bullet::init(int _x, int _y, double _angle, double _length)
{
	angle = _angle;
	length = _length;
	x = (double)_x;
	y = (double)_y;
	xVel = cos(angle) * length;;
	yVel = sin(angle) * length;
    return true;
    
}

void Bullet::show(SDL_Surface *screen)
{
	SDL_Rect r;
    x += xVel;
	y += yVel;
    if( ( x < 0 - BULLET_WIDTH ) || 
		( x > BULLET_WIDTH + SCREEN_WIDTH ) ||
		( y < 0 - BULLET_HEIGHT) || 
		( y > BULLET_HEIGHT + SCREEN_HEIGHT) )
    {
        toRemove = true;
    }
    r.x = x;
    r.y = y;
    SDL_BlitSurface(spriteBullet, NULL, screen, &r);
}

bool Bullet::getRemove()
{
	return toRemove;
}

int Bullet::getX(){ return x; }
int Bullet::getY(){ return y; }
int Bullet::getW(){ return spriteBullet->w; }
int Bullet::getH(){ return spriteBullet->h; }
