#include "game.hpp"
#include "player.hpp"
#include "turret.hpp"
#include "hud.hpp"

using namespace std;

Game::Game()
{
	end = false;
    bg = NULL;
    bgX = bgY = 0;
    bgSpeed = 1;
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
    SDL_FreeSurface(sUntouchPlayer);
    SDL_FreeSurface(sPlayerLife);
    SDL_FreeSurface(sTurret);
    SDL_FreeSurface(sbulletPlayer);
    SDL_FreeSurface(sbulletTurret);
    SDL_FreeSurface(levelTest);

    	
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
    sUntouchPlayer = SDL_LoadBMP(s.data());
    
    inputfile >> s;
    sPlayerLife = SDL_LoadBMP(s.data());
    
    inputfile >> s;
    sTurret = SDL_LoadBMP(s.data());
    
    inputfile >> s; 
    sbulletPlayer = SDL_LoadBMP(s.data());
    
    inputfile >> s; 
    sbulletTurret = SDL_LoadBMP(s.data());
    
    inputfile >> s;
    levelTest = SDL_LoadBMP(s.data());

    if( bg==NULL || sPlayer==NULL || sUntouchPlayer == NULL || sPlayerLife == NULL || sTurret==NULL || sbulletPlayer==NULL || sbulletTurret==NULL || levelTest==NULL)
	{
    	cout << "Problem loading pictures from the Game" << endl;
    	return false;
	}

	player = new Player(this, sPlayer, sUntouchPlayer);
	player->init(SCREEN_WIDTH/2, SCREEN_HEIGHT - PLAYER_HEIGHT);
	
	hud = new Hud(this, sPlayerLife);
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
		line.push_back(_imgLvl->h - y);
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

void Game::createEnemies()
{
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
	
	if(lvlInfos.size() >= 1)
	{
		nextInfo = (lvlInfos.back().front() - 1) * PSDL_PIMGLVL;
	}
	else
		nextInfo = bg->h ;
}

void Game::addPlayerBullet(Bullet * _bulletPlayer)
{
	bulletsPlayer.push_back(_bulletPlayer);
}

void Game::addEnemyBullet(Bullet * _bulletEnemy)
{
	bulletsEnnemys.push_back(_bulletEnemy);
}

void Game::show(SDL_Surface * _screen)
{
	SDL_Rect r;
	bgY += getBgSpeed(); 
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
		createEnemies();
	}
	if(lineBg < bg->h)
		lineBg++;
	else 
		setBgSpeed(0);
	

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
	player->show(_screen);
	hud->show(_screen);
	//Collision test 
	for (vector<Bullet *>::iterator itb = bulletsEnnemys.begin();itb != bulletsEnnemys.end();)
	{
		if((*itb)->collision(player))
		{		

			if(!player->getUntouchable())
			{
				player->setUntouchable(true);		
				player->setLifes(player->getLifes() - 1);	
				cout << "Player lifes "<< player->getLifes()<< endl;
			}
			bulletsEnnemys.erase(itb);				
			//break;
		}
		else 
			itb++;
	}
	if(SDL_GetTicks() - player->getTimeUntouchable() > TIME_UNTOUCHABLE)
		player->setUntouchable(false);
	
	bool deleteEnemy = false;		
	for (vector<Ship *>::iterator ite = enemys.begin();ite != enemys.end();)
	{
		for (vector<Bullet *>::iterator itb = bulletsPlayer.begin();itb != bulletsPlayer.end();)
		{
			if((*itb)->collision(*ite) )
			{					
				hud->changeScore(TURRET_POINT);
				bulletsPlayer.erase(itb);
				deleteEnemy = true;
			}
			else
				itb++;
		}
		if(deleteEnemy)		
			enemys.erase(ite);
		else		
			ite++;
		deleteEnemy = false;
	}	
	checkEnd();
}

void Game::checkEnd()
{
	if(player->getLifes() == 0)
		end = true;
}

bool Game::getEnd(){ return end; }
int Game::getBgSpeed(){ return bgSpeed; }
void Game::setBgSpeed(int _speed){ bgSpeed = _speed; }
SDL_Surface * Game::getSbulletPlayer(){ return sbulletPlayer; }
SDL_Surface * Game::getSbulletEnemy(){ return sbulletTurret; }
SDL_Surface * Game::getSPlayerLife(){ return sPlayerLife; }
Ship * Game::getPlayer(){ return player; }
