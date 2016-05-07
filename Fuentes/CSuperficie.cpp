#include "CSuperficie.h"
#include <SDL_image.h>
#include <iostream>


CSuperficie::CSuperficie()
{
   /// Constructor por defecto.
}

/// Carga en una superficie la imagen especificada por Ruta
/// optimizandola para que sea del mismo formato de pixel.
/// Uso:  sup_de_prueba = CSuperficie::Cargar("imagen.bmp")
SDL_Surface* CSuperficie::Cargar(char* Ruta)
{
   SDL_Surface* Sup_Temp     = NULL;
   SDL_Surface* Sup_Devuelta = NULL;
   if((Sup_Temp = IMG_Load(Ruta)) == NULL)
   {
      //cerr << "La imagen no se pudo cargar... :( " << SDL_GetError() << endl;
      return NULL;
   }
   Sup_Devuelta = SDL_DisplayFormat(Sup_Temp); /// Optimizo la imagen
   SDL_FreeSurface(Sup_Temp);                  /// Libero la original
   return Sup_Devuelta;                        /// Devuelvo la optimizada.
}

/// Dibuja en la sup de destino la que recibe como fuente en las coordenadas especificadas
bool CSuperficie::Dibujar(SDL_Surface* Sup_Dest, SDL_Surface* Sup_Fuente, int X, int Y)
{
   if(Sup_Dest == NULL || Sup_Fuente== NULL)
   {
      //cerr << "CSuperficie::Dibujar = Una de las superficies es NULL... :( " << SDL_GetError() << endl;
      return false;
   }
   SDL_Rect DestR;
   DestR.x = X;
   DestR.y = Y;
   SDL_BlitSurface(Sup_Fuente, NULL, Sup_Dest, &DestR);
   return true;
}

/// Dibuja en la sup de destino la que recibe como fuente en las coordenadas especificadas por X e Y
/// pero toma de la sup fuente el rectangulo formado por X2, Y2, W, H. Osea recorta la imagen fuente.
bool CSuperficie::Dibujar(SDL_Surface* Sup_Dest, SDL_Surface* Sup_Fuente, int X, int Y, int X2, int Y2, int W, int H)
{
   if(Sup_Dest == NULL || Sup_Fuente== NULL)
   {
      //cerr << "CSuperficie::Dibujar = Una de las superficies es NULL... :( " << SDL_GetError() << endl;
      return false;
   }
   SDL_Rect DestR;
   DestR.x = X;
   DestR.y = Y;
   SDL_Rect FuenR;
   FuenR.x = X2;
   FuenR.y = Y2;
   FuenR.w = W;
   FuenR.h = H;
   SDL_BlitSurface(Sup_Fuente, &FuenR, Sup_Dest, &DestR);
   return true;
}

/// Estable el color pasado en R, G, y B como transparente en
/// la superficie especificada. Por ejemplo: Rojo = R:255, G:0, B:0
bool CSuperficie::Transparente(SDL_Surface* Sup_Dest, int R, int G, int B)
{
   if(Sup_Dest == NULL)
   {
      //cerr << "La superficie recibida para establecerle la transparencia es NULL... :( " << SDL_GetError() << endl;
      return false;
   }
   SDL_SetColorKey(Sup_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Sup_Dest->format, R, G, B));
   return true;
}
