 #include "player.hpp"
 
 using namespace std;
 
 Player::Player(Game * _game):Ship(_game)
{
    previousTime = 0; 
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
	if (SDL_GetTicks() - previousTime > BULLET_TIME)
	{
		game->fireBullet();
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
