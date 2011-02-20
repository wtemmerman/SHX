#ifndef H_MENU
#define H_MENU

class Menu;

#include "constants.hpp"
#include "moteur.hpp"

class Menu
{
	private:
		SDL_Surface *images[4];	
		SDL_Rect jouer, quitter, titre;
	public:
		Menu();
		~Menu();

		bool init(std::string file);
		
		void clic(int x, int y);

		void aff(SDL_Surface *screen);
};

#endif
