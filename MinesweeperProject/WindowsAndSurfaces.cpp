#include "WindowsAndSurfaces.h"
#include <SDL.h>

SDL_Window* initWindow(int m,int n)
{   SDL_Window *w;
    w=NULL;
    w=SDL_CreateWindow("Minesweeper",100,100,n*50,m*50,SDL_WINDOW_SHOWN);
    return w;
}

void clean(SDL_Window* &w,SDL_Surface* &s)
{
    s=NULL;
    SDL_DestroyWindow(w);
    w=NULL;
    SDL_Quit();
}

void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect o,i= {0,0,50,50};
    o.x = x*50;
    o.y = y*50;
    o.h=50;
    o.w=50;
    SDL_BlitSurface( source,&i, destination, &o );
}
