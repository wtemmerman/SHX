 #include "player.hpp"
 
 using namespace std;
 
 Player::Player()
{
    x = 0;
    y = 0;

    xVel = 0;
    yVel = 0;
    
    sprite = NULL;
}

Player::~Player()
{
	SDL_FreeSurface(sprite);
}

bool Player::init(const char * file)
{
	x = SCREEN_WIDTH /2;
	y = SCREEN_WIDTH /2;
	if(sprite!=NULL)
	{
		SDL_FreeSurface(sprite), sprite = NULL;
	}
    sprite = SDL_LoadBMP(file);
    SDL_SetColorKey(sprite,SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( sprite->format, 0x00, 0x00, 0x00 ));
    if( sprite==NULL )
	{
    	cout << "Problem loading pictures from the Player" << endl;
    	return false;
	}
    return true;
    
}

void Player::handle_input(SDL_Event event)
{
    if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel -= PLAYER_HEIGHT / 5; break;
            case SDLK_DOWN: yVel += PLAYER_HEIGHT / 5; break;
            case SDLK_LEFT: xVel -= PLAYER_WIDTH / 5; break;
            case SDLK_RIGHT: xVel += PLAYER_WIDTH / 5; break;
            default: break;
        }
    }
    else if( event.type == SDL_KEYUP )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel += PLAYER_HEIGHT / 5; break;
            case SDLK_DOWN: yVel -= PLAYER_HEIGHT / 5; break;
            case SDLK_LEFT: xVel += PLAYER_WIDTH / 5; break;
            case SDLK_RIGHT: xVel -= PLAYER_WIDTH / 5; break;
            default: break;
        }
    }
}

void Player::show(SDL_Surface *screen)
{
	SDL_Rect r;
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
    SDL_BlitSurface(sprite, NULL, screen, &r);
}
