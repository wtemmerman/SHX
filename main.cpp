#include "moteur.hpp"
#include "constants.hpp"
Moteur moteur;

using namespace std;

int main(int argc, char **argv)
{
	SDL_Event event;
	SDL_Surface *screen;
	int done = 0;

	if(SDL_Init(SDL_INIT_VIDEO)!=0) {
		cout << "Probleme pour initialiser SDL: " << SDL_GetError() << endl;
		return 1;
	}

    SDL_WM_SetCaption("Shoot'em up xTrem", NULL);

	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT, SCREEN_BPP, SDL_DOUBLEBUF | SDL_HWSURFACE);
    if(screen==NULL)
      	done = 1;

    if(!moteur.init())
        return 1;

    while(!done)
    {
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					done=1;
					break;
				case SDL_KEYUP:
					if(event.key.keysym.sym==SDLK_q)
						moteur.fin();
					else if(event.key.keysym.sym==SDLK_ESCAPE)
						moteur.echangeFonctions();
					break;
				case SDL_MOUSEBUTTONUP:
					moteur.clic(event.button.x, event.button.y);
					break;
				default:
					break;
			}
		}

    moteur.aff(screen);
    moteur.verif();
    SDL_Flip(screen);
    }

	SDL_Quit();

    (void) argc;
    (void) argv;
	return 0;
}
