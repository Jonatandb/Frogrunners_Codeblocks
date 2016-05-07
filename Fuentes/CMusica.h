#ifndef _CMUSICA_H_
#define _CMUSICA_H_

#include <SDL.h>
#include <SDL_mixer.h>

class Musica
{
   public:
            Musica(char *ruta);
            void reproducir();
            void pausar();
            ~Musica();
   private:
            Mix_Music*        bso;
};

#endif
