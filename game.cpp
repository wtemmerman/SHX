#include "game.hpp"

using namespace std;

Game::Game()
{
    bg = NULL;
    bgX = bgY = 0;
    player = new Player();
}

Game::~Game()
{
    SDL_FreeSurface(bg);
}

bool Game::init(string file)
{
	bool playerInit;
    ifstream inputfile;
    string s;
 
    inputfile.open(file.data());

    if(inputfile.fail())
	{
        cout << "Error during the openning of file of init game" << file << endl;
        return false;
	}
	
    if(bg!=NULL)
	{
		SDL_FreeSurface(bg), bg = NULL;
	}
	
    inputfile >> s;
    bg = SDL_LoadBMP(s.data());
       
    inputfile >> s;  
    playerInit = player->init(s.data());
    if( (bg==NULL) || !playerInit)
	{
    	cout << "Problem loading pictures from the Game" << endl;
    	return false;
	}
    return true;
}

void Game::handle_input(SDL_Event event)
{
	player->handle_input(event);
}

void Game::show(SDL_Surface *screen)
{
	SDL_Rect r;
	bgY -= 2; 
	//If the background has gone too far 
	if( bgY <= -bg->h ) 
	{ 
		bgY = 0; 
	} 
	r.x = bgX; 
	r.y = bgY;
	SDL_BlitSurface(bg,NULL,screen,&r);
	r.x = bgX;
	r.y = bgY + bg->h;
    SDL_BlitSurface(bg,NULL,screen,&r);  
      
    player->show(screen);
}

void Game::checkEnd()
{
	//to do
}

bool Game::getEnd()
{
	return end;
}
