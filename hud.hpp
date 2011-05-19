#ifndef H_HUD
#define H_HUD

#include "constants.hpp"
#include "game.hpp"

class Hud
{
    private: 
		Game * game;
    	SDL_Surface * sLife, * sScore, *sScoreInt;
    	SDL_Rect posLife, posScore, posScoreInt;
    	TTF_Font * police;
    	SDL_Color white;
    	int score;    	
    	int lifes;	
    	char tabScore[20];
    public:
    	Hud(Game * _game, SDL_Surface * _sLife);
    	~Hud();
		void show(SDL_Surface * _screen);
		void changeScore(int _points);
};
#endif
