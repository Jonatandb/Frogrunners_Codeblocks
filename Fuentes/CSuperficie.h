#ifndef _CSUPERFICIE_H_
#define _CSUPERFICIE_H_
#include <SDL.h>

class CSuperficie
{
   public:
         CSuperficie();
   public:
         static SDL_Surface* Cargar(char* Ruta);
         static bool Dibujar(SDL_Surface* Sup_Dest, SDL_Surface* Sup_Fuente, int X, int Y);
         static bool Dibujar(SDL_Surface* Sup_Dest, SDL_Surface* Sup_Fuente, int X, int Y, int X2, int Y2, int W, int H);
         static bool Transparente(SDL_Surface* Sup_Dest, int R, int G, int B);
};

#endif
