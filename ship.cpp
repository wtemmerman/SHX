 #include "ship.hpp"
 
 using namespace std;
 
 Ship::Ship(Game * _game)
{
	game = _game;
	
    x = 0;
    y = 0;

    xVel = 0;
    yVel = 0;
    
    spriteShip = NULL;
}

Ship::~Ship()
{
	SDL_FreeSurface(spriteShip);
}

bool Ship::init(const char * file, int _x, int _y)
{
	x = _x;
	y = _y;
	if(spriteShip!=NULL)
	{
		SDL_FreeSurface(spriteShip);
		spriteShip = NULL;
	}
    spriteShip = SDL_LoadBMP(file);
    SDL_SetColorKey(spriteShip,SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( spriteShip->format, 0x00, 0x00, 0x00 ));
    if( spriteShip==NULL )
	{
    	cout << "Problem loading pictures from the Ship" << endl;
    	return false;
	}
    return true;
    
}

void Ship::show(SDL_Surface *screen)
{}

int Ship::getX()
{
	return x;
}

int Ship::getY()
{
	return y;
}

