#include "game.hpp"
#include "player.hpp"
#include "turret.hpp"

using namespace std;

Game::Game()
{
    bg = NULL;
    bgX = bgY = 0;
    bulletsPlayer = vector<Bullet *>();
    bulletsEnnemys = vector<Bullet *>();
    enemys = vector<Ship *>();
}

Game::~Game()
{
    SDL_FreeSurface(bg);
    SDL_FreeSurface(sPlayer);
    SDL_FreeSurface(sTurret);
    SDL_FreeSurface(sbulletPlayer);
    SDL_FreeSurface(sbulletTurret);
    for (vector<Bullet *>::iterator it = bulletsPlayer.begin(); 
			it != bulletsPlayer.end(); 
			it++)
		delete (*it);
	for (vector<Bullet *>::iterator it = bulletsEnnemys.begin(); 
			it != bulletsEnnemys.end(); 
			it++)
		delete (*it);
	for (vector<Ship *>::iterator it = enemys.begin(); 
			it != enemys.end(); 
			it++)
		delete (*it);
}

bool Game::init(string file)
{
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
    sPlayer = SDL_LoadBMP(s.data());
    
    inputfile >> s;
    sTurret = SDL_LoadBMP(s.data());
    
    inputfile >> s; 
    sbulletPlayer = SDL_LoadBMP(s.data());
    
    inputfile >> s; 
    sbulletTurret = SDL_LoadBMP(s.data());
    if( bg==NULL || sPlayer==NULL || sTurret==NULL || sbulletPlayer==NULL || sbulletTurret==NULL)
	{
    	cout << "Problem loading pictures from the Game" << endl;
    	return false;
	}
	player = new Player(this, sPlayer);
	player->init(SCREEN_WIDTH/2, SCREEN_HEIGHT - PLAYER_HEIGHT);
	Turret *t1, *t2;
	t1 = new Turret(this, sTurret);
	t2 = new Turret(this, sTurret);
	t1->init(300, 0);
	t2->init(450, 0);
	enemys.push_back(t1);
	enemys.push_back(t2);
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
    for (vector<Ship *>::iterator it = enemys.begin();it != enemys.end();it++)
	{
		(*it)->show(screen);	
	}
	for (vector<Bullet *>::iterator it = bulletsPlayer.begin();it != bulletsPlayer.end();)
	{
		if((*it)->getRemove())
			bulletsPlayer.erase(it);
		else 
		{
			(*it)->show(screen);
			it++;	
		}
	}	
	for (vector<Bullet *>::iterator it = bulletsEnnemys.begin();it != bulletsEnnemys.end();)
	{
		if((*it)->getRemove())
			bulletsEnnemys.erase(it);
		else 
		{
			(*it)->show(screen);
			it++;	
		}
	}
	//Collision test 
	for (vector<Bullet *>::iterator itb = bulletsPlayer.begin();itb != bulletsPlayer.end();itb++)
	{
		for (vector<Ship *>::iterator ite = enemys.begin();ite != enemys.end();ite++)
		{
			if(Collision((*ite), (*itb)))
				cout << "Bullet player touche enemys : o" << endl;
		}
	}
	
	for (vector<Bullet *>::iterator itb = bulletsEnnemys.begin();itb != bulletsEnnemys.end();itb++)
	{
		if(Collision(player, (*itb)))
			cout << "Bullet Enemy touche Player : o" << endl;
	}
}

void Game::fireBullet(int _type, int _x, int _y)
{
	Bullet * b = new Bullet();
	if(_type == TYPE_PLAYER)
	{
		if(!b->init(sbulletPlayer, _x, _y, 90, -3, _type))
			cout << "Problème lors de l initialisation d une bullet" << endl;
		bulletsPlayer.push_back(b);
	}
	if(_type == TYPE_TURRET)
	{
		double hypothenuse = sqrt(pow(player->getX() - _x,2) + pow(player->getY() - _y,2));
		double side = (double)player->getY() - _y;
		double angle = acos( side / hypothenuse);
		//cout << hypothenuse << " --- " << angle <<  " ---- " << player->getY() - turret->getY() << endl;
		if(!b->init(sbulletTurret, _x, _y, angle, hypothenuse/100, _type))
			cout << "Problème lors de l initialisation d une bullet" << endl;
		bulletsEnnemys.push_back(b);
	}
}

bool Game::Collision(Ship * _ship, Bullet * _bullet)
{
	if((_ship->getX() >= _bullet->getX()+ _bullet->getW())      // trop à droite
	|| (_ship->getY() +  _ship->getW()	<= _bullet->getX()) // trop à gauche
	|| (_ship->getY() >= _bullet->getY()+ _bullet->getH()) // trop en bas
	|| (_ship->getY() +  _ship->getH() 	<= _bullet->getY()))  // trop en haut
          return false; 
   else
          return true; 
}
void Game::checkEnd()
{
	//to do
}

bool Game::getEnd()
{
	return end;
}
