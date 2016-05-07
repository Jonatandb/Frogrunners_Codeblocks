#ifndef _CSONIDO_H_
#define _CSONIDO_H_
#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_mixer.h>
#include <vector>
class CSonido
{
   public:
            static CSonido     ControlSonido;
            vector<Mix_Chunk*> ListaSonidos;
            CSonido();
            int Cargar(char* Archivo);
            void Liberar_Recursos();
            void Reproducir(int ID);
};

#endif
