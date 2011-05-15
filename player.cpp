 #include "player.hpp"
 
 using namespace std;
 
 Player::Player(Game * game)
{
	game = game;
	
    x = 0;
    y = 0;

    xVel = 0;
    yVel = 0;
    
    spritePlayer = NULL;
}

Player::~Player()
{
	SDL_FreeSurface(spritePlayer);
}

bool Player::init(const char * file)
{
	x = SCREEN_WIDTH /2;
	y = SCREEN_WIDTH /2;
	if(spritePlayer!=NULL)
	{
		SDL_FreeSurface(spritePlayer);
		spritePlayer = NULL;
	}
    spritePlayer = SDL_LoadBMP(file);
    SDL_SetColorKey(spritePlayer,SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( spritePlayer->format, 0x00, 0x00, 0x00 ));
    if( spritePlayer==NULL )
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
            case SDLK_UP: yVel -= PLAYER_HEIGHT / 6; break;
            case SDLK_DOWN: yVel += PLAYER_HEIGHT / 10; break;
            case SDLK_LEFT: xVel -= PLAYER_WIDTH / 7; break;
            case SDLK_RIGHT: xVel += PLAYER_WIDTH / 7; break;
            case SDLK_SPACE: game->fireBullet();
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
    SDL_BlitSurface(spritePlayer, NULL, screen, &r);
}
