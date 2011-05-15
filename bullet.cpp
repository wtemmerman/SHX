 #include "bullet.hpp"
 
 using namespace std;
 
 Bullet::Bullet()
{
    x = 0;
    y = 0;

    xVel = 0;
    yVel = -3;
   
	toRemove = false;
	
    spriteBullet = NULL;
}

Bullet::~Bullet()
{
	SDL_FreeSurface(spriteBullet);
}

bool Bullet::init(SDL_Surface * _spriteBullet, int _x, int _y)
{
	x = _x + PLAYER_WIDTH/2 - BULLET_WIDTH/2;
	y = _y;
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
		cout << "toRemove is true now" << endl;
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
