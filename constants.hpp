#ifndef CONSTANTS_HPP
#define	CONSTANTS_HPP

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <string>
#include <fstream>

const double PI = 3.141592654;
const int LINE_IMGLVL = 32;
const int PSDL_PIMGLVL = 50; // 50 /1 

const int TYPE_PLAYER = 1;
const int TYPE_TURRET = 2;

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=600;
const int SCREEN_BPP=32;

const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 50;
const int PLAYER_LIFES = 20;

const int TURRET_WIDTH = 50;
const int TURRET_HEIGHT = 50;

const int BULLET_WIDTH = 5;
const int BULLET_HEIGHT = 5;

const unsigned int BULLET_TIME_PLAYER = 200;
const unsigned int BULLET_TIME_TURRET = 300;
const unsigned int TIME_UNTOUCHABLE = 3000;

const unsigned int WANTED_FPS = 40; // 1000/40 =  25 fps

#endif	/* CONSTANTS_HPP */
