#include "main.h"


void puttext(SDL_Surface **surface, char *text, int size, int r, int g, int b);
void setrect(SDL_Rect *rect, int x, int y, int w, int h);
void aplliquesprite( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
Image initimage(char* adresse,int w,int h);

SDL_Event event;

SDL_Color textcolor;
TTF_Font *font;

SDL_Surface *tfps, *ttexte, *tpause, *tscore, *screen *back; //peut ne servire a rien maintenant
SDL_Rect rtmp;  //rame tmp
Mix_Chunk *s;  // son 

Image ecran, fond, image; 
/*
typedef de Mix_Chunk { 
    int alloué ; 
    Uint8 * abuf ; 
    Uint32 Alen ; 
    Uint8 le volume ; / * Volume par échantillon, 0-128 * / 
} Mix_Chunk;
*/
Uint32 colorkey;  //int sur 32 bit



char nomprog[]= "monprog"; //non du programme
int score = 0;
int fps = 0;
int startticks, startticksf;

char gticks = 0;
char gticksf = 0;
char cfps[100];  //string
char cscore[100];    //string
char pause = 1;
char gameover = 0;
char win = 0;


SDL_Rect listesprite[ 14 ];     //sprite d'une image



int main(int argc, char **argv)
{	

	srand(time(NULL));
	int j,i,k;
	int loop = 1;
	//-----------------------------------initialisation chargement SDL--------------------------------------------------

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!=0)
    {
        printf("Initialisation impossible!!!");
        return 1;
    }
	TTF_Init(); //taille écriture
	SDL_WM_SetCaption(monprog, NULL);
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_DOUBLEBUF | SDL_HWSURFACE);
	
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	s = Mix_LoadWAV("poua.wav");
	if(s == NULL)
	{
		printf("!!");
		return 1;
	}
	image=initimage("BMP/image.png",longueur, largeur);

	colorkey = SDL_MapRGB(screen->format, 255, 255, 255);
	SDL_SetColorKey(apple, SDL_SRCCOLORKEY, colorkey);
	SDL_SetColorKey(spritesnake, SDL_SRCCOLORKEY, colorkey);
	back = SDL_AllocSurface(SDL_HWSURFACE, WIDTH, HEIGHT, BPP, 0, 0, 0, 0);
	puttext(&tpause, "Press Space", 90, 255, 255, 255);
	puttext(&tfps, "0 fps", 16, 160, 0, 0);
	puttext(&tscore, "Score : 0", 22, 0, 0, 0);
	puttext(&ttest, "teste", taillepolice, 255, 60, 60);
	
	image.sprite=listesprite;
	//vertical
	listesprite[ 0 ].x = 40;
	listesprite[ 0 ].y = 20;
	listesprite[ 0 ].w = 20;
	listesprite[ 0 ].h = 20;
	//horizontal
	listesprite[ 1 ].x = 20;
	listesprite[ 1 ].y = 0;
	listesprite[ 1 ].w = 20;
	listesprite[ 1 ].h = 20;
	

	setrect(&rtmp, 0, 0, WIDTH, 40);
	SDL_FillRect(back, &rtmp, SDL_MapRGB(screen->format, 100, 100, 255));  //remplire un rectangle
	if(screen==NULL) loop = 0;
	while(loop)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                	loop = 0;
                	break;
                case SDL_KEYDOWN:
                	if(event.key.keysym.sym == SDLK_a) loop = 0;
					
					if(event.key.keysym.sym == SDLK_DOWN)
					{
						//....
					}
					if(event.key.keysym.sym == SDLK_UP)
					{
						//...
					}
					if(event.key.keysym.sym == SDLK_RIGHT)
					{
						//...
					}
					if(event.key.keysym.sym == SDLK_LEFT)
					{
						//...
					}
					
					if(event.key.keysym.sym == SDLK_SPACE)
					{
						pause = 1 - pause;
						if(!pause && (gameover || win))
						{
							//resset game
					}
					break;
				default:
                	break;
            }
        }
		
		if(!gticks)
		{
			startticks = SDL_GetTicks();  //Renvoie le nombre de millisecondes écoulées depuis la bibliothèque SDL initialisation. Cette valeur entoure si le programme dure plus de 49,7 jours.
			gticks = 1;
		}
		if((SDL_GetTicks() - startticks) >= 50)
		{
			if((!pause && !gameover)||(!pause && !win))
			{
				//boucle jeux



				gticks = 0;
			}
			//affichage
			SDL_BlitSurface(back, NULL, screen, NULL);
			setrect(&rtmp, positionx, positiony + 40, 0, 0); //+40 du a la bordu en haut
			SDL_BlitSurface(image.im, NULL, screen, &rtmp);		
			
			
		}
		fps++;
		if(gticksf == 0) 
		{	
			startticksf = SDL_GetTicks();
			gticksf = 1;
		}	
		if(SDL_GetTicks() - startticksf >= 1000)
		{
			gticksf = 0;
			sprintf(cfps, "%d fps", fps);
			puttext(&tfps, cfps, 16, 160, 0, 0);
			fps = 0;
		}
		if(pause) 
		{
			setrect(&rtmp, 120, 180, 0, 0);
			SDL_BlitSurface(tpause, NULL, screen, &rtmp);
		}
		if(gameover && win){
			setrect(&rtmp, 130, 300, 0, 0);
			SDL_BlitSurface(tbisou, NULL, screen, &rtmp);
			pause = 1;
		}
		else{
			if(gameover)
			{
				setrect(&rtmp, 130, 300, 0, 0);
				SDL_BlitSurface(tgameover, NULL, screen, &rtmp);
				pause = 1;
			}
			if(win){
				setrect(&rtmp, 130, 300, 0, 0);
				SDL_BlitSurface(twin, NULL, screen, &rtmp);
				pause = 1;
			}
		}
		setrect(&rtmp, 700, 10, 0, 0);
		SDL_BlitSurface(tfps, NULL, screen, &rtmp);
		setrect(&rtmp, 30, 10, 0, 0);
		SDL_BlitSurface(tscore, NULL, screen, &rtmp);
		SDL_Flip(screen);		
	}

    SDL_Quit();
    SDL_FreeSurface(tfps);SDL_FreeSurface(tpause);SDL_FreeSurface(tscore);SDL_FreeSurface(tgameover);//SDL_FreeSurface(screen);
    SDL_FreeSurface(sprite1);SDL_FreeSurface(grass);SDL_FreeSurface(back);SDL_FreeSurface(apple);SDL_FreeSurface(spritesnake);
    SDL_FreeSurface(spritesnake2); //free(ma);
    printf("Fin programme\n");
    return 0;
}


void puttext(SDL_Surface **surface, char *text, int size, int r, int g, int b)
{
	textcolor.r = r;
	textcolor.g = g;
	textcolor.b = b;
	font = TTF_OpenFont("Roman.ttf", size);
	SDL_FreeSurface(*surface);
	*surface = TTF_RenderText_Solid(font, text, textcolor);
	TTF_CloseFont(font);
}

void setrect(SDL_Rect *rect, int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}
/*
void aplliquesprite( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    SDL_Rect offset;
 
    offset.x = x;
    offset.y = y;
    //offset.h = 0;
    //offset.w = 0;
 
    //On blitte la surface
    SDL_BlitSurface( source, clip, destination, &offset );
}*/
// a tester
Image initimage(char* adresse,int w,int h){
	Image image;
	SDL_Surface *im;
	if((im = IMG_Load(adresse))==NULL){
		perror("IMG_Load");
		printf("erreur de lecture %s\n",adresse);
		exit(1);
	}
	image.w=w;
	image.h=h;
	image.image=im;
	image.sprite=NULL;
	return(image);
}
