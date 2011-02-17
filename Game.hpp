#ifndef GAME_HPP
#define	GAME_HPP

#include "Constants.hpp"
#include "Player.hpp"
#include <string>

class Game
{
    private:
		//Structure d'évènement
		SDL_Event event;    
    	//Surfaces d'un player et d'un background
    	SDL_Surface * screen, *player, *bg;   	
        //Déclaration des variables
        int gameState , fps, last, now;
        unsigned int checkTime;
		Player * myPlayer;
    public:
    	//Créateur/Destructeur
    	Game(SDL_Surface * screen);
    	~Game();

        //Fonction gérant le jeu
        bool launch(); 
        //Fonction d'initialisation (chargement des surfaces)
        bool init();      
		SDL_Surface *load_image( std::string filename );
    	//Fonction d'affichage
    	void show(SDL_Surface *screen);
};

#endif	/* GAME_HPP */
