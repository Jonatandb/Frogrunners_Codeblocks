#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "CMusica.h"
#include "Configuraciones.h"

using namespace std;

Musica::Musica(char *ruta)
{
   bso = Mix_LoadMUS(ruta);
   if(bso == NULL)
   {
      cerr << "La Música no se pudo cargar... :( " << SDL_GetError() << endl;
      exit(1);
   }
   Mix_VolumeMusic(VOLUMEN_MUSICA);
}

void Musica::reproducir()
{
   Mix_PlayMusic(bso, -1);
}

void Musica::pausar()
{
   Mix_PauseMusic();
}

Musica::~Musica()
{
   Mix_FreeMusic(bso);
}
