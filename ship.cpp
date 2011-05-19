#include "ship.hpp"
#include "game.hpp"
#include "bullet.hpp"
  
using namespace std;
 
Ship::Ship(Game * _game, SDL_Surface * _spriteShip, SDL_Surface * _sUntouchable)
{
	game = _game;
	spriteShip = _spriteShip;
	sUntouchable =  _sUntouchable;
	toRemove = false;
	untouchable = false;
	previousTime = 0;
	
    x = 0;
    y = 0;

    xVel = 0;
    yVel = 0;
    
    lifes = 0;
    if(spriteShip != NULL)
		SDL_SetColorKey(spriteShip,SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( spriteShip->format, 0xff, 0x00, 0xff ));
	if(sUntouchable != NULL)
		SDL_SetColorKey(sUntouchable,SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( sUntouchable->format, 0xff, 0x00, 0xff ));
}

Ship::~Ship()
{
	delete game;
	if(spriteShip != NULL)
		SDL_FreeSurface(spriteShip);
	if(sUntouchable != NULL)
		SDL_FreeSurface(sUntouchable);
}

bool Ship::init(int _x, int _y)
{
	x = _x;
	y = _y;
	if( spriteShip==NULL )
	{
    	cout << "Problem loading pictures from the Ship" << endl;
    	return false;
	}
    SDL_SetColorKey(spriteShip,SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( spriteShip->format, 0xff, 0x00, 0xff ));
    return true;
}

void Ship::shoot()
{}
void Ship::show(SDL_Surface *screen)
{}
bool Ship::collision(Bullet * _bullet)
{}
int Ship::getH()
{}
int Ship::getW()
{}
int Ship::getLifes()
{}
void Ship::setLifes(int _lifes)
{}

bool Ship::getRemove(){	return toRemove; }
void Ship::setRemove(bool _toRemove){ toRemove = _toRemove; }
int Ship::getX(){ return x; }
int Ship::getY(){ return y; }
void Ship::setUntouchable(bool _state)
{ 
	if(_state)
		timeUntouchable = SDL_GetTicks();
	untouchable = _state;		
		
}	
bool Ship::getUntouchable(){ return untouchable; }
Uint32 Ship::getTimeUntouchable(){ return timeUntouchable; }

