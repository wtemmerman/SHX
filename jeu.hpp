#ifndef H_JEU
#define H_JEU

#include <fstream>

#include "constants.hpp"

class Jeu
{
    private: 
    	SDL_Surface *bg;
		int bgX, bgY; 
    	bool fini;
        void verifFini();
    public:
    	Jeu();
    	~Jeu();

        bool init(std::string file);
    	void aff(SDL_Surface *screen);
    	bool getFini();
};
#endif

