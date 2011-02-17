#include "Game.hpp"

Game::Game(SDL_Surface * screen)
{
    gameState = 0;
    //Pour le calcul des FPS
    last = SDL_GetTicks()/1000;
    fps = 0;

    //Pour le taux de rafraichissement
    checkTime = SDL_GetTicks();
    
    //Valeur par défaut pour les surfaces
    screen = screen;
    player = NULL;
    bg = NULL;
}

Game::~Game()
{
    //On libére les surfaces
    SDL_FreeSurface(player);
    SDL_FreeSurface(bg);
}

/*SDL_Surface *load_image( std::string filename )
{
    //L'image qui est chargée
    SDL_Surface* loadedImage = NULL;
    //L'image optimisée qu'on va utiliser
    SDL_Surface* optimizedImage = NULL;
    //Chargement de l'image
    loadedImage = IMG_Load( filename.c_str() );
    //Si l'image a bien chargée
    if( loadedImage != NULL )
    {
        //Création de l'image optimisée
        optimizedImage = SDL_DisplayFormat( loadedImage );
        //Libération de l'ancienne image
        SDL_FreeSurface( loadedImage );
        //Si la surface a bien été optimisée
        if( optimizedImage != NULL )
        {
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0, 0 ) );
        }
    }

    //On retourne l'image optimisée
    return optimizedImage;
}*/

bool Game::init()
{
    //Vérification de l'allocation des surfaces
    if(player!=NULL)
    {
        SDL_FreeSurface(player);
        player = NULL;
    }
    if(bg!=NULL)
    {
        SDL_FreeSurface(bg);
        bg = NULL;
    }

    //On charge toutes les images dans les surfaces associées
    player = SDL_LoadBMP("player.bmp");
    bg = SDL_LoadBMP("bg.bmp");

    //On teste le retour du chargement
    if( (player==NULL) || (bg==NULL))
    {
    	printf("Probleme de chargement des surfaces \n");
    	return false;
    }

    return true;
}

bool Game::launch()
{
	myPlayer = new Player(&event);
    //Boucle generale
    while(!gameState)
    {
        //Traiter les evenements
        while(SDL_PollEvent(&event))
        {
            myPlayer->handle_input();
            switch(event.type)
            {
                    case SDL_QUIT:
                            gameState=1;
                            break;
                    case SDL_KEYUP:
                            if(event.key.keysym.sym==SDLK_q)
                                gameState=1;
                            break;
                    default:
                            break;
            }
        }

        if(SDL_GetTicks() > (checkTime + 1000 / wantedfps) )
        {
            // On met a jour la variable checkTime
            checkTime = SDL_GetTicks();

            // On incremente la variable fps
            fps++;
            // Gerer l'affichage du fps
            now = time(NULL);
            if(now!=last)
            {
                printf("FPS: %d\n",fps/(now-last));;
                last = now;
                fps = 0;
            }

            // Demander au moteur de dessiner la scene
            myPlayer->move();
            show(screen);
            SDL_Flip(screen);
        }
        else
        {
            // Attendre 5 millisecondes
            SDL_Delay(5);
        }
    }
    return false;
}

void Game::show(SDL_Surface * screen)
{
    //Dessiner le fond d'ecran
    SDL_BlitSurface(bg, NULL, screen, NULL);
    SDL_BlitSurface(player, NULL, screen, &myPlayer->getLocality());
}
