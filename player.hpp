#ifndef H_PLAYER
#define	H_PLAYER

#include "constants.hpp"
#include "ship.hpp"

class Game;

class Player : public Ship
{
    private:
		SDL_Surface * sUntouchable;
        int previousTime;
        bool untouchable;
        Uint32 timeUntouchable;
    public:
        Player(Game * _game, SDL_Surface * _spriteShip, SDL_Surface * _spriteUntouch);
        virtual ~Player();
        void handle_input(SDL_Event event);
        void show(SDL_Surface * screen);
        void shoot();
        int getH();
        int getW();
        int getLifes();
        void setLifes(int _lifes);
        void setUntouchable(bool _state);
        bool getUntouchable();
        Uint32 getTimeUntouchable();
 };

#endif	
