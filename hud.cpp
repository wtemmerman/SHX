#include "hud.hpp"

using namespace std; 
	
Hud::Hud(Game * _game, SDL_Surface * _sLife)
{
	game = _game;
	sLife = _sLife;
	SDL_SetColorKey(sLife,SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( sLife->format, 0xff, 0x00, 0xff ));
	
	lifes = 0;
	score = 0;
	
	police = TTF_OpenFont("angelina.TTF", 22);	
	posLife.x = SCREEN_WIDTH + 5;
	posLife.y = 5;
	white.r = 255;
	white.g = 255;
	white.b = 255;
	
	sprintf(tabScore,"%d", score);
	
	sScore = TTF_RenderText_Solid(police, "Score", white);
	posScore.x = posLife.x;
	posScore.y = (game-> getPlayer()->getLifes()) * (game->getSPlayerLife()->h + 5) + 5;
	
	sScoreInt = TTF_RenderText_Solid(police, tabScore , white);
	posScoreInt.x = SCREEN_WIDTH_HUD - 10;
	posScoreInt.y = posScore.y + 22;
	
}

Hud::~Hud()
{
	SDL_FreeSurface(sLife);
	SDL_FreeSurface(sScore);
	SDL_FreeSurface(sScoreInt);
	TTF_CloseFont(police);
}

void Hud::show(SDL_Surface * _screen)
{	
	posLife.y = 5;
	lifes = game-> getPlayer()->getLifes();
	for(int i = 0; i < lifes; i++)
	{
		SDL_BlitSurface(sLife, NULL, _screen, &posLife);
		posLife.y += 45;
	}
	SDL_BlitSurface(sScore, NULL, _screen, &posScore);
	SDL_BlitSurface(sScoreInt, NULL, _screen, &posScoreInt);
}

void Hud::changeScore(int _points)
{
	score += _points;
	posScoreInt.x =  SCREEN_WIDTH_HUD - 10*(int) (1 + log10(score));
	sprintf(tabScore,"%d", score);
	SDL_FreeSurface(sScoreInt);
	sScoreInt = TTF_RenderText_Solid(police, tabScore , white);
}
