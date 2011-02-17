/* 
 * File:   main.cpp
 * Author: wiL
 *
 * Created on 15 février 2011, 18:01
 */
#include "Game.hpp"
#include "time.h"
#include <cstdio>

bool init(SDL_Surface * screen)
{
    //Initialisation de SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return false;
    }

    //Ouvrerture d'une surface pour l'affichage de la fenêtre
    screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT, SCREEN_BPP, SDL_DOUBLEBUF | SDL_HWSURFACE);
    if(screen==NULL)
        return false;

    //Mettre un titre à la fenêtre
    SDL_WM_SetCaption("Shoot'em up Xtreme", NULL);
    return true;
}

void clean_up(SDL_Surface * screen)
{
    //Libération surface
    SDL_FreeSurface(screen);
    //On quitte SDL
    SDL_Quit();
}

int main(int argc, char** argv)
{
	SDL_Surface * screen = NULL;
	
    bool inGame = true;
    if( !init(screen) )
    {
        printf( "Can't init SDL:  %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }

    Game game(screen);

    if(game.init()==false)
        return 1;
        
    while(inGame)
    {
        if(!game.launch())
            inGame = false;
    }
    clean_up(screen);   
    return 0;
}

