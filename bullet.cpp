 #include "bullet.hpp"
 
 using namespace std;
 
 Bullet::Bullet()
{
    x = 0;
    y = 0;

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

bool Bullet::init(SDL_Surface * _spriteBullet, int _x, int _y, double _angle, double _length,int _type)
{
	type = _type;
	if(type == TYPE_PLAYER)
	{
		x = _x + PLAYER_WIDTH/2 - BULLET_WIDTH/2;
		y = _y;
		angle = PI * (_angle) / 180 ;
	}
	else if(type == TYPE_TURRET)
	{
		x = _x + TURRET_WIDTH/2 - BULLET_WIDTH/2;
		y = _y + TURRET_HEIGHT/2 - BULLET_HEIGHT/2;
		angle = _angle;
	}
	length = _length;
	//cout << "INIT : " << _type << " " << angle << " " << length << endl;
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
    x += cos(angle) * length;
	y += sin(angle) * length;
	//cout << "SHOW : "<< type << " "  << x << " " << y << endl;
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
int Bullet::getW(){ return BULLET_WIDTH; }
int Bullet::getH(){ return BULLET_HEIGHT; }
