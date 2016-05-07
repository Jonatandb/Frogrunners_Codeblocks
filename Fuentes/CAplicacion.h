#ifndef _CAPLICACION_H_
#define _CAPLICACION_H_
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Configuraciones.h"
#include "CEntidad.h"
#include "CEvento.h"
#include "CSuperficie.h"
#include "CAnimacion.h"
#include "CSonido.h"
#include "CMusica.h"

class CAplicacion : public CEvento  /// Hereda de la Clase CEvento por lo que puede consumir sus metodos.
{
   public:
            CAplicacion();
            int      Ejecutar();
            bool     Inicializacion();
            void     Presentacion();
            void     Menu_Principal();
            void     Menu_Opciones();
            void     Juego();
            void     Manejar_Eventos(SDL_Event*);
            void     Hacer_Calculos();
            void     Dibujar();
            void     Liberar_Recursos();
            void     Salir();
            void     TeclaPresionada(SDLKey sym, SDLMod mod, Uint16 unicode);
            void     BotonIzqMousePresionado(int mX, int mY);
            void     BotonIzqMouseSoltado(int mX, int mY);
            int      sonido_opcion_elegida;

   private:
            bool           funcionando;
            bool           menu_visible;
            bool           dibujar_menu;
            bool           menu_opciones_visible;
            bool           dibujar_menu_opciones;
            bool           pantalla_completa;
            bool           actualizar_pantalla;
            bool           mostrar_presentacion;
            bool           juego_visible;
            bool           dibujar_juego;
            bool           actualizar_musica;
            bool           musica_activa;
            bool           sonido_activo;

            SDL_Surface*   pantalla;
            Musica         musica;
            SDL_Event      Event;
            CEntidad       rana1;
};

#endif
