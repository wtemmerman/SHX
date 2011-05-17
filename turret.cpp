#include "turret.hpp"
#include "game.hpp"
 
using namespace std;
 
Turret::Turret(Game * _game, SDL_Surface * _spriteShip):Ship(_game, _spriteShip)
{
    previousTime = 0; 
    yVel = 1;
    toRemove = false;
}

Turret::~Turret()
{}

void Turret::show(SDL_Surface * screen)
{
	SDL_Rect r;	

	if (SDL_GetTicks() - previousTime > BULLET_TIME_TURRET)
	{
		game->fireBullet(TYPE_TURRET, getX(), getY());
		previousTime = SDL_GetTicks();
	}	
	if( ( x < 0 - TURRET_WIDTH ) || 
		( x > TURRET_WIDTH + SCREEN_WIDTH ) ||
		//( y < 0 - TURRET_HEIGHT) || 
		( y > TURRET_HEIGHT + SCREEN_HEIGHT) )
    {
        setRemove(true);
    }
    y += yVel;
    r.x = x;
    r.y = y;
    SDL_BlitSurface(spriteShip, NULL, screen, &r);
}

int Turret::getH(){ return TURRET_HEIGHT; }
int Turret::getW(){ return TURRET_WIDTH; }
