#include "Player.hpp"

Player::Player(SDL_Event * playerEvent)
{
	event = playerEvent;
    locality.x = SCREEN_WIDTH/2;
    locality.y = SCREEN_HEIGHT/2;
    locality.w = PLAYER_WIDTH;
    locality.y = PLAYER_HEIGHT;

    //Initialisation de la vitesse
    xVel = 0;
    yVel = 0;
}

void Player::handle_input()
{
    //Si une touche a ete pressee
    if( event->type == SDL_KEYDOWN )
    {
        //ajustement de la vitesse
        switch( event->key.keysym.sym )
        {
            case SDLK_UP: yVel -= PLAYER_HEIGHT / 5; break;
            case SDLK_DOWN: yVel += PLAYER_HEIGHT / 5; break;
            case SDLK_LEFT: xVel -= PLAYER_WIDTH / 5; break;
            case SDLK_RIGHT: xVel += PLAYER_WIDTH / 5; break;
            default: break;
        }
    }
    //Si une touche a ete relachee
    else if( event->type == SDL_KEYUP )
    {
        //ajustement de la vitesse
        switch( event->key.keysym.sym )
        {
            case SDLK_UP: yVel += PLAYER_HEIGHT / 5; break;
            case SDLK_DOWN: yVel -= PLAYER_HEIGHT / 5; break;
            case SDLK_LEFT: xVel += PLAYER_WIDTH / 5; break;
            case SDLK_RIGHT: xVel -= PLAYER_WIDTH / 5; break;
            default: break;
        }
    }
}

void Player::move()
{
    //Bouge le point à gauche ou à droite
    locality.x += xVel;

    //Si le point se rapproche trop des limites(gauche ou droite) de l'ecran
    if( ( locality.x < 0 ) || ( locality.x + PLAYER_WIDTH > SCREEN_WIDTH ) )
    {
        //On revient
        locality.x -= xVel;
    }

    //Bouge le point en haut ou en bas
    locality.y += yVel;

    //Si le point se rapproche trop des limites(haute ou basse) de l'ecran
    if( ( locality.y < 0 ) || ( locality.y + PLAYER_HEIGHT > SCREEN_HEIGHT ) )
    {
        //On revient
        locality.y -= yVel;
    }
}

SDL_Rect Player::getLocality()
{
    return locality;
}
