#include "turret.hpp"
#include "game.hpp"
 
using namespace std;
 
Turret::Turret(Game * _game, SDL_Surface * _spriteShip):Ship(_game, _spriteShip)
{
    previousTime = 0; 
    yVel = _game->getBgSpeed();
    toRemove = false;
}

Turret::~Turret()
{}

void Turret::show(SDL_Surface * screen)
{
	SDL_Rect r;	

	if (SDL_GetTicks() - previousTime > BULLET_TIME_TURRET)
	{
		shoot();
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

void Turret::shoot()
{
	Bullet * b = new Bullet();
	//double angle = atan2( _y - player->getY(), _x - player->getX());
	double angle = atan2(game->getPlayer()->getX() - getX(), game->getPlayer()->getY() - getY());
	if(!b->init(game->getSbulletEnemy(), 
				getX() + TURRET_WIDTH/2 - BULLET_WIDTH/2,
				getY() + TURRET_HEIGHT/2 - BULLET_HEIGHT/2, 
				angle, 3))
		cout << "Problème lors de l initialisation d une bullet" << endl;
	game->addEnemyBullet(b);
}

int Turret::getH(){ return TURRET_HEIGHT; }
int Turret::getW(){ return TURRET_WIDTH; }
