#include "game.hpp"
#include "bullet.hpp"

using namespace std;

Game::Game()
{
    bg = NULL;
    bgX = bgY = 0;
    bulletsPlayer = vector<Bullet>();
}

Game::~Game()
{
    SDL_FreeSurface(bg);
    SDL_FreeSurface(bullet);
    for (vector<Bullet>::iterator it = bulletsPlayer.begin(); 
			it != bulletsPlayer.end(); 
			it++)
       bulletsPlayer.erase(it);
}

bool Game::init(string file)
{
	player = new Player(this);
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

    inputfile >> s; 
    bullet = SDL_LoadBMP(s.data());
    if( bg==NULL || !playerInit || bullet==NULL)
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
	bgY += 2; 
	//If the background has gone too far 
	if( bgY >= 0 ) 
	{ 
		bgY = -bg->h; 
	} 
	r.x = bgX; 
	r.y = bgY;
	SDL_BlitSurface(bg,NULL,screen,&r);
	r.x = bgX;
	r.y = bgY + bg->h;
    SDL_BlitSurface(bg,NULL,screen,&r);  
      
    player->show(screen);
   /* for (unsigned int i = 0; i < bulletsPlayer.size(); i++)
	{
		cout<< "loOOOOOOOOOol"<< endl;
		if((*it)->getRemove())
			bulletsPlayer.erase(it);
		else
			(*it)->show(screen);
	}*/
}

void Game::fireBullet()
{
	Bullet b;
	b.init(bullet);
	bulletsPlayer.push_back(b);
	cout<< "PushBack done"  << bulletsPlayer.size() << endl;
}
void Game::checkEnd()
{
	//to do
}

bool Game::getEnd()
{
	return end;
}

SDL_Surface * Game::getBulletSurface()
{
	return bullet;
}
