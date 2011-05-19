#include "player.hpp"
#include "game.hpp"
 
using namespace std;
 
Player::Player(Game * _game, SDL_Surface * _spriteShip, SDL_Surface * _spriteUntouch):Ship(_game,_spriteShip, _spriteUntouch)
{
    setLifes(PLAYER_LIFES);
}

Player::~Player()
{}

void Player::handle_input(SDL_Event event)
{
    if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel -= PLAYER_HEIGHT / 6; break;
            case SDLK_DOWN: yVel += PLAYER_HEIGHT / 10; break;
            case SDLK_LEFT: xVel -= PLAYER_WIDTH / 7; break;
            case SDLK_RIGHT: xVel += PLAYER_WIDTH / 7; break;
            default: break;
        }
    }
    else if( event.type == SDL_KEYUP )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel += PLAYER_HEIGHT / 6; break;
            case SDLK_DOWN: yVel -= PLAYER_HEIGHT / 10; break;
            case SDLK_LEFT: xVel += PLAYER_WIDTH / 7; break;
            case SDLK_RIGHT: xVel -= PLAYER_WIDTH / 7; break;
            default: break;
        }
    }
}


void Player::show(SDL_Surface *screen)
{
	if (SDL_GetTicks() - previousTime > BULLET_TIME_PLAYER)
	{
		shoot();
		previousTime = SDL_GetTicks();
	}
	if(SDL_GetTicks() - getTimeUntouchable() > TIME_UNTOUCHABLE)
		setUntouchable(false);
	SDL_Rect r;
	//cout << "x " << xVel << "y " << yVel << endl;
    x += xVel;
    if( ( x < 0 ) || ( x + spriteShip->w > SCREEN_WIDTH ) )
    {
        x -= xVel;
    }
   
    y += yVel;
    if( ( y < 0 ) || ( y + spriteShip->h  > SCREEN_HEIGHT ) )
    {
        y -= yVel;
    }
    r.x = x;
    r.y = y;
    if(untouchable)
		SDL_BlitSurface(sUntouchable, NULL, screen, &r);
	else
		SDL_BlitSurface(spriteShip, NULL, screen, &r);
}

void Player::shoot()
{
	Bullet * bullet = new Bullet(game->getSbulletPlayer());
	//double angle = atan2( _y - player->getY(), _x - player->getX());
	double angle = atan2( -1, 0);
	if(!bullet->init(getX() + spriteShip->w /2,
					getY(), 
					angle, LENGTH_SHOOT_PLAYER))
		cout << "Problème lors de l initialisation d une bullet" << endl;
	game->addPlayerBullet(bullet);
}

bool Player::collision(Bullet * _bullet)
{
	if((_bullet->getX() >= this->getX()+ this->getW())      // trop à droite
	|| (_bullet->getX() +  _bullet->getW()	<= this->getX()) // trop à gauche
	|| (_bullet->getY() >= this->getY()+ this->getH()) // trop en bas
	|| (_bullet->getY() +  _bullet->getH() 	<= this->getY()))  // trop en haut
          return false; 
   else
          return true; 
}

int Player::getH(){ return spriteShip->h; }
int Player::getW(){ return spriteShip->w; }
int Player::getLifes(){ return lifes; }
void Player::setLifes(int _lifes){ lifes = _lifes; }
