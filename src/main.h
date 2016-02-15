#ifndef MAIN
#define MAIN

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include <errno.h>
const int WIDTH = 1200;
const int HEIGHT = 700;
const int BPP = 24;

typedef struct{
	int w;  //longueur
	int h;  //largeur
	SDL_Surface image;
	SDL_Rect sprite;
}Image;

#endif