#include "turret.hpp"
#include "game.hpp"
 
using namespace std;
 
Turret::Turret(Game * _game, SDL_Surface * _spriteShip, SDL_Surface * _spriteUntouch):Ship(_game,_spriteShip, _spriteUntouch)
{
    yVel = _game->getBgSpeed();
    toRemove = false;
    setLifes(TURRET_LIFES);
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
	if( ( x < 0 - spriteShip->w ) || 
		( x > spriteShip->w + SCREEN_WIDTH ) ||
		//( y < 0 - TURRET_HEIGHT) || 
		( y > spriteShip->h + SCREEN_HEIGHT)
		|| getLifes() == 0 )
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
	Bullet * bullet = new Bullet(game->getSbulletEnemy());
	double angle = atan2( game->getPlayer()->getY() - getY(),game->getPlayer()->getX() - getX());
	if(!bullet->init(getX() + spriteShip->w/2 - bullet->getW()/2,
					getY() + spriteShip->h/2 - bullet->getH()/2, 
					angle, LENGTH_SHOOT))
		cout << "Problème lors de l initialisation d une bullet" << endl;
	game->addEnemyBullet(bullet);
}

bool Turret::collision(Bullet * _bullet)
{
	if((_bullet->getX() >= this->getX()+ this->getW())      // trop à droite
	|| (_bullet->getX() +  _bullet->getW()	<= this->getX()) // trop à gauche
	|| (_bullet->getY() >= this->getY()+ this->getH()) // trop en bas
	|| (_bullet->getY() +  _bullet->getH() 	<= this->getY()))  // trop en haut
          return false; 
   else
          return true; 
}

int Turret::getH(){ return spriteShip->h; }
int Turret::getW(){ return spriteShip->w; }
int Turret::getLifes(){ return lifes; }
void Turret::setLifes(int _lifes){ lifes += _lifes; }
