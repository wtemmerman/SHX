 #include "bullet.hpp"
 
 using namespace std;
 
 Bullet::Bullet()
{
    x = 0;
    y = 0;
	xVel = 0;
	yVel = 0;
	
    angle = 0.0;
    length = 0.0;
   
	toRemove = false;
	
	type = 0;
	
    spriteBullet = NULL;
}

Bullet::~Bullet()
{
	SDL_FreeSurface(spriteBullet);
}

bool Bullet::init(SDL_Surface * _spriteBullet, int _x, int _y, double _angle, double _length)
{
	angle = _angle;
	length = _length;
	x = _x;
	y = _y;
	xVel = cos(angle) * length;;
	yVel = sin(angle) * length;
	if(spriteBullet != NULL)
	{
		SDL_FreeSurface(spriteBullet);
		spriteBullet = NULL;
	}
    spriteBullet = _spriteBullet;

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

bool Bullet::collision(Ship * _ship)
{
	if((_ship->getX() >= this->getX()+ this->getW())      // trop à droite
	|| (_ship->getX() +  _ship->getW()	<= this->getX()) // trop à gauche
	|| (_ship->getY() >= this->getY()+ this->getH()) // trop en bas
	|| (_ship->getY() +  _ship->getH() 	<= this->getY()))  // trop en haut
          return false; 
   else
          return true; 
}

bool Bullet::getRemove()
{
	return toRemove;
}

int Bullet::getX(){ return x; }
int Bullet::getY(){ return y; }
int Bullet::getW(){ return BULLET_WIDTH; }
int Bullet::getH(){ return BULLET_HEIGHT; }
