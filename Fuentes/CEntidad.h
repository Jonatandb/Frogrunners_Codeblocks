#include <iostream>
using namespace std;
#include <vector>
#include "CAnimacion.h"
#include "CSuperficie.h"

class CEntidad
{
   public:
            static vector<CEntidad*>   ListaEntidades;
            CEntidad();
            virtual ~CEntidad();
    public:
            float             X;
            float             Y;
            int               Width;
            int               Height;
            int               EstadoAnimacion;
            virtual bool      Cargar(char* Archivo, int Width, int Height, int MaxFrames);
            virtual void      Hacer_Loop();
            virtual void      Dibujar(SDL_Surface* Pantalla);
            virtual void      Liberar_Recursos();
            SDL_Surface*      Sup_Entidad;
   protected:
            CAnimacion        ControlAnimacion;

};
