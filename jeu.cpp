#include "jeu.hpp"

using namespace std;

Jeu::Jeu()
{
    bg=NULL;
    bgX = bgY = 0;
}

Jeu::~Jeu()
{
    SDL_FreeSurface(bg);
}

bool Jeu::init(string file)
{
    ifstream inputfile;
    string s;
 
    inputfile.open(file.data());

    if(inputfile.fail())
	{
        cout << "Erreur dans l'ouverture de " << file << endl;
        return false;
	}
	
    if(bg!=NULL)
	{
		SDL_FreeSurface(bg), bg = NULL;
	}
    
    inputfile >> s;
    bg = SDL_LoadBMP(s.data());
        
    if((bg==NULL))
	{
    	cout << "Probleme de chargement des images du jeu" << endl;
    	return false;
	}
    return true;
}

void Jeu::aff(SDL_Surface *screen)
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
}

void Jeu::verifFini()
{
	//a faire
}

bool Jeu::getFini()
{
	return fini;
}
