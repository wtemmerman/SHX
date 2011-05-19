#include "engine.hpp"

using namespace std;

Engine::Engine()
{
	menu = new Menu();
	game = new Game();
	inMenu = true;
}

Engine::~Engine()
{
	delete game;
	delete menu;
}

bool Engine::init()
{
	ifstream input;
	string s1,s2;
	
	input.open("data/input.txt");
	
	input >> s1 >> s2;
	return (game->init(s1) && (menu->init(s2)));
}

int Engine::handle_input(SDL_Event event)
{
	bool res = 0;
	switch(event.type)
	{
		case SDL_QUIT:
			res = 1;
			break;
		case SDL_KEYUP:
			if(event.key.keysym.sym==SDLK_q)
				end();
			else if(event.key.keysym.sym==SDLK_ESCAPE)
				switchFonctions();
			else
				game->handle_input(event);
			break;
		case SDL_KEYDOWN:
				game->handle_input(event);
			break;
		case SDL_MOUSEBUTTONUP:
			clic(event.button.x, event.button.y);
			break;
		default: 
			break;
	}
	return res;
}

void Engine::clic(int x, int y)
{
	if(inMenu)
	{
		menu->clic(x,y);
	}
}

void Engine::show(SDL_Surface * screen)
{
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	if(inMenu)
	{
		menu->show(screen);
	}
	else
	{
		game->show(screen);
	}
}

void Engine::switchFonctions()
{
	inMenu = !inMenu;
}

void Engine::setFonctionsGame()
{
	inMenu = false;
}

void Engine::setFonctionsMenu()
{
	inMenu = true;
}

void Engine::end()
{
	SDL_Event ev;
	ev.type = SDL_QUIT;
	SDL_PushEvent(&ev);
}

void Engine::check()
{
    if(!inMenu)
	{	
        if(game->getEnd())
        {
			cout << "Game Over" << endl;
			end();
		}
	}
}

