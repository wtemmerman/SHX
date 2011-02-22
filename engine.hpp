#ifndef H_ENGINE
#define H_ENGINE

class Engine;

#include "constants.hpp"
#include "menu.hpp"
#include "game.hpp"

class Engine
{
	private:
		Menu * menu;
		Game * game;
		bool inMenu;
	public:
		Engine();
		~Engine();

		void clic(int , int);
		void show(SDL_Surface *screen);

		bool init();

		int handle_input(SDL_Event event);
		void setFonctionsGame();
		void setFonctionsMenu();
		void switchFonctions();
		
		void end();
		void check();
};

#endif
