#include "moteur.hpp"

using namespace std;

Moteur::Moteur()
{
	menu = new Menu();
	jeu = new Jeu();
	dansMenu = true;
}

Moteur::~Moteur()
{
	delete jeu;
	delete menu;
}

bool Moteur::init()
{
	ifstream input;
	string s1,s2;
	
	input.open("data/input.txt");
	
	input >> s1 >> s2;
	return (jeu->init(s1) && (menu->init(s2)));
}

void Moteur::clic(int x, int y)
{
	if(dansMenu)
	{
		menu->clic(x,y);
	}
	else
	{	
		if(jeu->getFini())
			cout<< "test get fini" << endl;
		else
			cout<< "test else get fini" << endl;
	}
}

void Moteur::aff(SDL_Surface *screen)
{
	if(dansMenu)
	{
		menu->aff(screen);
	}
	else
	{
		jeu->aff(screen);
	}
}

void Moteur::initJeu()
{
	cout<< "test init jeu fini" << endl;
	//jeu->videJeu(); 
}

void Moteur::echangeFonctions()
{
	dansMenu = !dansMenu;
}

void Moteur::setFonctionsJeu()
{
	dansMenu = false;
}

void Moteur::setFonctionsMenu()
{
	dansMenu = true;
}

void Moteur::fin()
{
	SDL_Event ev;
	ev.type = SDL_QUIT;
	SDL_PushEvent(&ev);
}

void Moteur::verif()
{
    if(!dansMenu)
	{	
        if(!jeu->getFini())
        {
			cout<< "Jeu n'est pas fini" << endl;
		}
	}
}

