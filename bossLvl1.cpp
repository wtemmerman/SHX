#include "bossLvl1.hpp"
#include "game.hpp"

using namespace std;
 
BossLvl1::BossLvl1(Game * _game, SDL_Surface * _spriteShip):Ship(_game, _spriteShip)
{
    previousTime = 0; 
    futurPos = 0;
    xVel = 3;
    yVel = _game->getBgSpeed();
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
	if( ( x < 0 - spriteShip->w ) || 
		( x > spriteShip->w  + SCREEN_WIDTH ) ||
		//( y < 0 - TURRET_HEIGHT) || 
		( y > spriteShip->h  + SCREEN_HEIGHT) 
		|| getLifes() == 0 )
    {
        setRemove(true);
    }
    cout << " : " << futurPos<< " : "  << getX()<< " : "  << x << " : " << xVel<< " : "  << endl;
    if(futurPos == getX() || (futurPos-getX() <= xVel && futurPos-getX() >= -xVel))
		futurPos = rand()%400;
	if(futurPos < getX())
		x -= xVel;
	else
		x += xVel;
	cout << " : " << futurPos<< " : "  << getX()<< " : "  << x << " : " << xVel<< " : "  << endl;
	if(y < 0)
		y += yVel;
    r.x = x;
    r.y = y;
    SDL_BlitSurface(spriteShip, NULL, screen, &r);
    cout << "boss lifes " << getLifes() << endl;
}

void BossLvl1::shoot()
{
	Bullet * b1 = new Bullet();
	Bullet * b2 = new Bullet();
	double angleB1 = atan2( game->getPlayer()->getY() - getY(),game->getPlayer()->getX() - getX());
	if(!b1->init(game->getSbulletEnemy(), 
				getX() + spriteShip->w/5 - BULLET_WIDTH/2,
				getY() + spriteShip->h/5 - BULLET_HEIGHT/2, 
				angleB1, LENGTH_SHOOT))
		cout << "Problème lors de l initialisation d une bullet" << endl;
	double angleB2 = atan2( game->getPlayer()->getY() - getY(),game->getPlayer()->getX() - getX());
	if(!b2->init(game->getSbulletEnemy(), 
				getX() + spriteShip->w/2 - BULLET_WIDTH/2,
				getY() + spriteShip->h/2 - BULLET_HEIGHT/2, 
				angleB2, LENGTH_SHOOT))
		cout << "Problème lors de l initialisation d une bullet" << endl;
	game->addEnemyBullet(b1);
	game->addEnemyBullet(b2);
}

bool BossLvl1::collision(Bullet * _bullet)
{
	if((_bullet->getX() >= this->getX()+ this->getW())      // trop à droite
	|| (_bullet->getX() +  _bullet->getW()	<= this->getX()) // trop à gauche
	|| (_bullet->getY() >= this->getY()+ this->getH()) // trop en bas
	|| (_bullet->getY() +  _bullet->getH() 	<= this->getY()))  // trop en haut
          return false; 
   else
          return true; 
}

int BossLvl1::getH(){ return spriteShip->h; }
int BossLvl1::getW(){ return spriteShip->w; }
int BossLvl1::getLifes(){ return lifes; }
void BossLvl1::setLifes(int _lifes){ lifes += _lifes; }

