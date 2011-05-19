#include "bossLvl1.hpp"
#include "game.hpp"

using namespace std;
 
BossLvl1::BossLvl1(Game * _game, SDL_Surface * _spriteShip, SDL_Surface * _spriteUntouch):Ship(_game,_spriteShip, _spriteUntouch)
{  
    futurPos = 0;
    xVel = 3;
    yVel = _game->getBgSpeed();
    turret1.x = 35;
    turret1.y = 40;
    turret2.x = 158;
    turret2.y = 168;
    turret1.h = turret2.h = 30;
    turret1.w = turret2.w = 10;
    toRemove = false;
    setLifes(BOSS_LIFES);
    srand ( time(NULL) );
}

BossLvl1::~BossLvl1()
{}

void BossLvl1::show(SDL_Surface * screen)
{
	SDL_Rect r;	

	if (SDL_GetTicks() - previousTime > BULLET_TIME_BOSS)
	{
		shoot();
		previousTime = SDL_GetTicks();
	}	
	if(SDL_GetTicks() - getTimeUntouchable() > TIME_UNTOUCHABLE)
		setUntouchable(false);
	if( ( x < 0 - spriteShip->w ) || 
		( x > spriteShip->w  + SCREEN_WIDTH ) ||
		//( y < 0 - TURRET_HEIGHT) || 
		( y > spriteShip->h  + SCREEN_HEIGHT) 
		|| getLifes() == 0 )
    {
        setRemove(true);
    }
    
    if(futurPos == getX() || (futurPos-getX() <= xVel && futurPos-getX() >= -xVel))
		futurPos = rand()%600;
	if(futurPos < getX())
		x -= xVel;
	else
		x += xVel;
	if(y < 0)
		y += yVel;
    r.x = x;
    r.y = y;
    if(untouchable)
		SDL_BlitSurface(sUntouchable, NULL, screen, &r);
	else
		SDL_BlitSurface(spriteShip, NULL, screen, &r);
}

void BossLvl1::shoot()
{
	Bullet * bullet1 = new Bullet(game->getSbulletEnemy());
	Bullet * bullet2 = new Bullet(game->getSbulletEnemy());
	double angleB1 = atan2( game->getPlayer()->getY() - getY(),game->getPlayer()->getX() - getX() + xVel);
	if(!bullet1->init(getX() + spriteShip->w/5,
					getY() + spriteShip->h/1, 
					angleB1, LENGTH_SHOOT))
		cout << "Problème lors de l initialisation d une bullet" << endl;
	double angleB2 = atan2( game->getPlayer()->getY() - getY(),game->getPlayer()->getX() - getX());
	if(!bullet2->init(getX() + spriteShip->w/1.25,
					getY() + spriteShip->h/1, 
					angleB2, LENGTH_SHOOT))
		cout << "Problème lors de l initialisation d une bullet" << endl;
	game->addEnemyBullet(bullet1);
	game->addEnemyBullet(bullet2);
}

bool BossLvl1::collision(Bullet * _bullet)
{
	bool touchT1 = false;
	bool touchT2 = false;
	// turret 1
	if((_bullet->getX() >= turret1.x + turret1.w + getX())      // trop à droite
	|| (_bullet->getX() +  _bullet->getW()	<= turret1.x + getX()) // trop à gauche
	|| (_bullet->getY() >= turret1.y + turret1.h + getY()) // trop en bas
	|| (_bullet->getY() +  _bullet->getH() 	<= turret1.y + getY()))  // trop en haut
          touchT1 = false; 
    else
          touchT1 = true;
	if((_bullet->getX() >= turret2.x + turret2.w + getX())      // trop à droite
	|| (_bullet->getX() +  _bullet->getW()	<= turret2.x + getX()) // trop à gauche
	|| (_bullet->getY() >= turret2.y + turret2.h + getY()) // trop en bas
	|| (_bullet->getY() +  _bullet->getH() 	<= turret2.y + getY()))  // trop en haut
          touchT2 =  false; 
   else
          touchT2 = true;
   return (touchT1 || touchT2) ? true : false;
}

int BossLvl1::getH(){ return spriteShip->h; }
int BossLvl1::getW(){ return spriteShip->w; }
int BossLvl1::getLifes(){ return lifes; }
void BossLvl1::setLifes(int _lifes){ lifes += _lifes; }
