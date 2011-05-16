#include "turret.hpp"
#include "game.hpp"
 
using namespace std;
 
Turret::Turret(Game * _game, SDL_Surface * _spriteShip):Ship(_game, _spriteShip)
{
    previousTime = 0; 
    yVel = 2;
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

    y += yVel;
    r.x = x;
    r.y = y;
    SDL_BlitSurface(spriteShip, NULL, screen, &r);
}

int Turret::getH(){ return TURRET_HEIGHT; }
int Turret::getW(){ return TURRET_WIDTH; }
