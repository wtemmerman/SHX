#include "menu.hpp"

using namespace std;

extern Engine engine;

Menu::Menu()
{
	int i;
	for(i=0;i<4;i++)
		pictures[i] = NULL;
}

Menu::~Menu()
{
	int i;
	for(i=0;i<4;i++)
	{
		SDL_FreeSurface(pictures[i]) , pictures[i] = NULL;
	}
}

bool Menu::init(string file)
{
	int i;
	ifstream input;
	string name;
	
	input.open(file.c_str());

	if(input.fail())
	{
		cout << "Error during the openning of file of init menu " << file << endl;
		return false;
	}

	input >> name;

	pictures[0] = SDL_LoadBMP(name.c_str());
	
	input >> name;
	pictures[1] = SDL_LoadBMP(name.c_str());
	
	input >> title.x >> title.y;
	
	input >> name;
	pictures[2] = SDL_LoadBMP(name.c_str());
	
	input >> play.x >> play.y;
	
	input >> name;
	pictures[3] = SDL_LoadBMP(name.c_str());

	for(i=1;i<4;i++)
		SDL_SetColorKey(pictures[i],SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( pictures[i]->format, 0xff, 0x00, 0xff ));

	input >> exit.x >> exit.y;
	
	play.w = pictures[2]->w;
	play.h = pictures[2]->h;
	
	exit.w = pictures[3]->w;
	exit.h = pictures[3]->h;

	input.close();

	return true;
}

void Menu::clic(int x, int y)
{
	//button nouveau?
	if((play.x<x)&&(play.x+play.w>x)&&(play.y<y)&&(play.y+play.h>y))
	{
		engine.setFonctionsGame();
	}
	//button quitter?
	else if((exit.x<x)&&(exit.x+exit.w>x)&&(exit.y<y)&&(exit.y+exit.h>y))
		engine.end();
}

void Menu::show(SDL_Surface *screen)
{
	if(pictures[0] && pictures[1] && pictures[2] && pictures[3])
	{
		SDL_BlitSurface(pictures[0],NULL,screen,NULL);
		SDL_BlitSurface(pictures[1],NULL,screen,&title);
		SDL_BlitSurface(pictures[2],NULL,screen,&play);
		SDL_BlitSurface(pictures[3],NULL,screen,&exit);
	}
}
