#ifndef H_MENU
#define H_MENU

class Menu;

#include "constants.hpp"
#include "engine.hpp"

class Menu
{
	private:
		SDL_Surface * pictures[4];	
		SDL_Rect play, exit, title;
	public:
		Menu();
		~Menu();

		bool init(std::string file);		
		void clic(int x, int y);
		void show(SDL_Surface *screen);
};

#endif
