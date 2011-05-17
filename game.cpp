#include "game.hpp"
#include "player.hpp"
#include "turret.hpp"

using namespace std;

Game::Game()
{
	end = false;
    bg = NULL;
    bgX = bgY = 0;
    lineBg = 600;
    nextInfo = 0;
    bulletsPlayer = vector<Bullet *>();
    bulletsEnnemys = vector<Bullet *>();
    enemys = vector<Ship *>();
    lvlInfos = vector<vector<int > >();
}

Game::~Game()
{
    SDL_FreeSurface(bg);
    SDL_FreeSurface(sPlayer);
    SDL_FreeSurface(sTurret);
    SDL_FreeSurface(sbulletPlayer);
    SDL_FreeSurface(sbulletTurret);
    for (vector<Ship *>::iterator it = enemys.begin(); 
			it != enemys.end(); 
			it++)
		delete (*it);
    for (vector<Bullet *>::iterator it = bulletsPlayer.begin(); 
			it != bulletsPlayer.end(); 
			it++)
		delete (*it);
	for (vector<Bullet *>::iterator it = bulletsEnnemys.begin(); 
			it != bulletsEnnemys.end(); 
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
    
    inputfile >> s;
    levelTest = SDL_LoadBMP(s.data());

    if( bg==NULL || sPlayer==NULL || sTurret==NULL || sbulletPlayer==NULL || sbulletTurret==NULL || levelTest==NULL)
	{
    	cout << "Problem loading pictures from the Game" << endl;
    	return false;
	}
	player = new Player(this, sPlayer);
	player->init(SCREEN_WIDTH/2, SCREEN_HEIGHT - PLAYER_HEIGHT);
	
	loadLevel(levelTest);

    return true;
}

void Game::handle_input(SDL_Event event)
{
	player->handle_input(event);
}

Uint32 Game::getPixel(SDL_Surface *surface, int x, int y)
{
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;
    switch(nbOctetsParPixel)
    {
        case 1:
            return *p;
 
        case 2:
            return *(Uint16 *)p;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32 *)p;
        default:
            return 0; 
    }
}

void Game::loadLevel(SDL_Surface * _imgLvl)
{
	vector<int> line = vector<int>();
	Uint8 r, g, b;
	Uint32 pixel;
	int enemysOnLigne = 0;
	for(int y = 0; y < _imgLvl->h; y++)
	{
		line.push_back(LINE_IMGLVL - y);
		for(int x = 0; x < _imgLvl->w; x++)
		{		
			pixel = getPixel(_imgLvl, x, y);
			SDL_GetRGB(pixel, _imgLvl->format, &r, &g, &b);
			if((int)r== 255 && (int)g == 0 && (int)b == 0)
			{
				line.push_back(x);
				enemysOnLigne++;
			}			
		}		
		if(enemysOnLigne == 0)
			line.pop_back();
		else
			lvlInfos.push_back(line);
		line.clear();
		enemysOnLigne = 0;
	}
}

void Game::createEnemys()
{
	vector<vector<int > >::reverse_iterator it = lvlInfos.rbegin();
	for(unsigned int i = lvlInfos.back().size()-1; i > 0; i--)
	{	
		Turret *t;
		t = new Turret(this, sTurret);
		if(nextInfo < SCREEN_HEIGHT)
		{
			t->init(lvlInfos.back()[i]*PSDL_PIMGLVL, SCREEN_HEIGHT - lvlInfos.back().front() * PSDL_PIMGLVL);
		}
		else
		{
			t->init(lvlInfos.back()[i]*PSDL_PIMGLVL, -PSDL_PIMGLVL);
		}
		enemys.push_back(t);
	}
	lvlInfos.pop_back();
	nextInfo = (lvlInfos.back().front() - 1) * PSDL_PIMGLVL;
}

void Game::show(SDL_Surface * _screen)
{
	SDL_Rect r;
	bgY += 1; 
	//If the background has gone too far 
	if( bgY >= 0 ) 
	{ 
		bgY = -bg->h; 
	} 
	r.x = bgX; 
	r.y = bgY;
	SDL_BlitSurface(bg,NULL,_screen,&r);
	r.x = bgX;
	r.y = bgY + bg->h;
    SDL_BlitSurface(bg,NULL,_screen,&r);  
        
    while(nextInfo < lineBg)
    {
		createEnemys();
	}
	lineBg++;
	
    player->show(_screen);
    for (vector<Ship *>::iterator it = enemys.begin();it != enemys.end();)
	{
		if((*it)->getRemove())
			enemys.erase(it);
		else 
		{
			(*it)->show(_screen);
			it++;	
		}
	}
	for (vector<Bullet *>::iterator it = bulletsPlayer.begin();it != bulletsPlayer.end();)
	{
		if((*it)->getRemove())
			bulletsPlayer.erase(it);
		else 
		{
			(*it)->show(_screen);
			it++;	
		}
	}	
	for (vector<Bullet *>::iterator it = bulletsEnnemys.begin();it != bulletsEnnemys.end();)
	{
		if((*it)->getRemove())
			bulletsEnnemys.erase(it);
		else 
		{
			(*it)->show(_screen);
			it++;	
		}
	}
	
	//Collision test 
	for (vector<Ship *>::iterator ite = enemys.begin();ite != enemys.end();ite++)
	{
		for (vector<Bullet *>::iterator itb = bulletsPlayer.begin();itb != bulletsPlayer.end();)
		{
			if(Collision(*ite, *itb))
			{
				cout << "Bullet player touche enemys : o" << endl;
				bulletsPlayer.erase(itb);
				enemys.erase(ite);
			}
			else
				itb++;
		}
	}
	
	if(!player->getUntouchable())
	{
		for (vector<Bullet *>::iterator itb = bulletsEnnemys.begin();itb != bulletsEnnemys.end();)
		{
			if(Collision(player, (*itb)))
			{
				bulletsEnnemys.erase(itb);
				player->setUntouchable(true);
				cout << "Player intouchable" << endl;
				player->setLifes(player->getLifes() - 1);
				cout << "Player a " << player->getLifes() << "maintenant" << endl;
			}
			else 
				itb++;
		}
	}
	if(SDL_GetTicks() - player->getTimeUntouchable() > TIME_UNTOUCHABLE)
		player->setUntouchable(false);
	checkEnd();
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
		double side = (double)player->getX() - _x;
		if(player->getX() < _x)
			side = -side;
		double angle = acos( side / hypothenuse);
		//cout << hypothenuse << " --- " << angle <<  " ---- " << player->getX() - _x << endl;
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
	if(player->getLifes() < 0)
		end = true;
}

bool Game::getEnd()
{
	return end;
}
