#include "engine.hpp"
#include "constants.hpp"

Engine engine;

using namespace std;

int main(int argc, char **argv)
{
	SDL_Event event;
	SDL_Surface *screen;
	int done = 0, start;

	if(SDL_Init(SDL_INIT_VIDEO)!=0) {
		cout << "Problem for init SDL : " << SDL_GetError() << endl;
		return 1;
	}
    SDL_WM_SetCaption("Shoot'em up xTrem", NULL);

	screen = SDL_SetVideoMode(SCREEN_WIDTH_HUD,SCREEN_HEIGHT, SCREEN_BPP, SDL_DOUBLEBUF | SDL_HWSURFACE);
    if(screen==NULL)
      	done = 1;

    if(!engine.init())
        return 1;
        
    while(!done)
    {
		start = SDL_GetTicks();
		while(SDL_PollEvent(&event))
		{
			done = engine.handle_input(event);
		}

		engine.show(screen);
		engine.check();
		SDL_Flip(screen);
		
		if((SDL_GetTicks() - start) < 1000 / WANTED_FPS )
		{ 
			 SDL_Delay(( 1000 / WANTED_FPS ) - (SDL_GetTicks() - start));
		} 
    }
	SDL_Quit();

    (void) argc;
    (void) argv;
	return 0;
}
