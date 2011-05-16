 #include "ship.hpp"
 #include "game.hpp"
 
 using namespace std;
 
 Ship::Ship(Game * _game, SDL_Surface * _spriteShip)
{
	game = _game;
	spriteShip = _spriteShip;
	
	toRemove = false;
	
    x = 0;
    y = 0;

    xVel = 0;
    yVel = 0;
}

Ship::~Ship()
{
	SDL_FreeSurface(spriteShip);
}

bool Ship::init(int _x, int _y)
{
	x = _x;
	y = _y;
	if( spriteShip==NULL )
	{
    	cout << "Problem loading pictures from the Ship" << endl;
    	return false;
	}
    SDL_SetColorKey(spriteShip,SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( spriteShip->format, 0xff, 0x00, 0xff ));
    return true;
}

void Ship::show(SDL_Surface *screen)
{}
int Ship::getH()
{}
int Ship::getW()
{}

bool Ship::getRemove(){	return toRemove; }
void Ship::setRemove(bool _toRemove){ toRemove = _toRemove; }
int Ship::getX(){ return x; }
int Ship::getY(){ return y; }

