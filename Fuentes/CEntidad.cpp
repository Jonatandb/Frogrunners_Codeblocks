#include "CEntidad.h"
vector<CEntidad*> CEntidad::ListaEntidades;

CEntidad::CEntidad()
{
   Sup_Entidad = NULL;
   X = Y = 0.0f;
   Width = Height = 0;
   EstadoAnimacion = 0;
}

CEntidad::~CEntidad()
{

}

bool CEntidad::Cargar(char* Archivo, int Width, int Height, int MaxFrames)
{
   if((Sup_Entidad = CSuperficie::Cargar(Archivo)) == NULL)
   {
      return false;
   }
   CSuperficie::Transparente(Sup_Entidad, 255, 0, 255);  /// Por defecto el rosado es el trasparente, se puede cambiar.
   this->Width = Width;
   this->Height = Height;
   ControlAnimacion.MaxFrames = MaxFrames;
   return true;
}

void CEntidad::Hacer_Loop()
{
   ControlAnimacion.Animar();
}

void CEntidad::Dibujar(SDL_Surface* Pantalla)
{
   if(Sup_Entidad == NULL || Pantalla == NULL)
   {
      return;
   }
   CSuperficie::Dibujar(Pantalla, Sup_Entidad, X, Y, EstadoAnimacion * Width, ControlAnimacion.GetCurrentFrame() * Height, Width, Height);
}

void CEntidad::Liberar_Recursos()
{
   if(Sup_Entidad)
   {
      SDL_FreeSurface(Sup_Entidad);
   }
   Sup_Entidad = NULL;
}
