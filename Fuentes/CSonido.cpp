#include "CSonido.h"
#include "CAplicacion.h"

CSonido CSonido::ControlSonido;

CSonido::CSonido()
{
}

int CSonido::Cargar(char* Archivo)
{
   Mix_Chunk* SonidoTemp = NULL;
   if((SonidoTemp = Mix_LoadWAV(Archivo)) == NULL)
   {
      return -1;
   }
   ListaSonidos.push_back(SonidoTemp);
   return (ListaSonidos.size() - 1);
}

void CSonido::Liberar_Recursos()
{
   for(int i = 0;i < (int)ListaSonidos.size();i++)
   {
      Mix_FreeChunk(ListaSonidos[i]);
   }
   ListaSonidos.clear();
}

void CSonido::Reproducir(int ID)
{
   /// de alguna manera necesito saber si el
   /// sonido esta activo desde aca para no reproducir
   /// ninguno cunado eso no se cumpla.

   //if(Frogrunners.sonido_activo)
   //{
      if(ID < 0 || ID >= (int)ListaSonidos.size())
      {
         return;
      }
      if(ListaSonidos[ID] == NULL)
      {
         return;
      }
      Mix_PlayChannel(-1, ListaSonidos[ID], 0);
   //}
}
