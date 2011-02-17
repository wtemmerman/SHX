#ifndef PLAYER_HPP
#define	PLAYER_HPP

#include "Constants.hpp"

class Player
{
    private:
        //Les coordonnées x et y du point
        int x, y;

        //La vitesse du point
        int xVel, yVel;

        SDL_Rect locality;
		SDL_Event * event;
    public:
        //Initialisation des variables
        Player(SDL_Event * playerEvent);

        //Recupere la touche pressee et ajuste la vitesse du point
        void handle_input();

        //Appliquer la surface
        void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );

        //Montre le point sur l'ecran
        void move();

        //getter sur la localisation du player
        SDL_Rect getLocality();
};

#endif	/* PLAYER_HPP */
