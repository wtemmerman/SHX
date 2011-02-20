#include "menu.hpp"

using namespace std;

extern Moteur moteur;

Menu::Menu()
{
	int i;
	for(i=0;i<4;i++)
		images[i] = NULL;
}

Menu::~Menu()
{
	int i;
	for(i=0;i<4;i++)
	{
		SDL_FreeSurface(images[i]) , images[i] = NULL;
	}
}

bool Menu::init(string file)
{
	int i;
	ifstream input;
	string nom;
	
	input.open(file.c_str());

	if(input.fail())
	{
		cout << "Erreur dans l'ouverture du fichier " << file << endl;
		return false;
	}

	input >> nom;

	images[0] = SDL_LoadBMP(nom.c_str());
	
	input >> nom;
	images[1] = SDL_LoadBMP(nom.c_str());
	
	input >> titre.x >> titre.y;
	
	input >> nom;
	images[2] = SDL_LoadBMP(nom.c_str());
	
	input >> jouer.x >> jouer.y;
	
	input >> nom;
	images[3] = SDL_LoadBMP(nom.c_str());

	//Mise en place de la transparence	
	for(i=1;i<4;i++)
		SDL_SetColorKey(images[i],SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( images[i]->format, 0xff, 0x00, 0xff ));

	input >> quitter.x >> quitter.y;
	
	jouer.w = images[2]->w;
	jouer.h = images[2]->h;
	
	quitter.w = images[3]->w;
	quitter.h = images[3]->h;

	input.close();

	return true;
}

void Menu::clic(int x, int y)
{
	//Est-ce qu'on est dans le bouton nouveau?
	if((jouer.x<x)&&(jouer.x+jouer.w>x)&&(jouer.y<y)&&(jouer.y+jouer.h>y))
	{
		moteur.initJeu();
		moteur.setFonctionsJeu();
	}
	//Est-ce qu'on est dans le bouton quitter?
	else if((quitter.x<x)&&(quitter.x+quitter.w>x)&&(quitter.y<y)&&(quitter.y+quitter.h>y))
		moteur.fin();
}

void Menu::aff(SDL_Surface *screen)
{
	//Si on a une image, on l'affiche
	if(images[0] && images[1] && images[2] && images[3])
	{
		SDL_BlitSurface(images[0],NULL,screen,NULL);
		SDL_BlitSurface(images[1],NULL,screen,&titre);
		SDL_BlitSurface(images[2],NULL,screen,&jouer);
		SDL_BlitSurface(images[3],NULL,screen,&quitter);
	}
}
