#include "player.hpp"
#include "game.hpp"
 
using namespace std;
 
Player::Player(Game * _game, SDL_Surface * _spriteShip):Ship(_game,_spriteShip)
{
    previousTime = 0; 
    
    lifes = 3;
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
		game->fireBullet(TYPE_PLAYER, getX(), getY());
		previousTime = SDL_GetTicks();
	}
	SDL_Rect r;
	//cout << "x " << xVel << "y " << yVel << endl;
    x += xVel;
    if( ( x < 0 ) || ( x + PLAYER_WIDTH > SCREEN_WIDTH ) )
    {
        x -= xVel;
    }
   
    y += yVel;
    if( ( y < 0 ) || ( y + PLAYER_HEIGHT > SCREEN_HEIGHT ) )
    {
        y -= yVel;
    }
    r.x = x;
    r.y = y;
    SDL_BlitSurface(spriteShip, NULL, screen, &r);
}

int Player::getH(){ return PLAYER_HEIGHT; }
int Player::getW(){ return PLAYER_WIDTH; }
int Player::getLifes(){ return lifes; }
void Player::setLifes(int _lifes){ lifes = _lifes; }
