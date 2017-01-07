#include <SDL.h>

SDL_Window* initWindow(int m,int n);
void clean(SDL_Window* &w,SDL_Surface* &s);
void applySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
