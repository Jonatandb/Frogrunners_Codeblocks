/************************************************************************
*
*                              Frogrunners
*
*************************************************************************
*  Autor: Bonet Jonatan
*  Email: jonatandb@hotmail.com
*  Compilador: Codeblocks
*************************************************************************
*  Fecha: 01/11/2009
*  Copyright 2009
************************************************************************/

#include <iostream>
#include "CAplicacion.h"

using namespace std;



int main(int argc, char* argv[])
{
   CAplicacion Frogrunners;
   return Frogrunners.Ejecutar();
}


/*
-PASOS BASICOS PARA TRABAJAR CON UNA SUPERFICIE:
   -Declararla (generalmente en CAplicacion.h)
   -Setearla a NULL (en el constructor de la aplicacion)
   -Cargarle una imagen (en el metodo inicializacion)
   -Dibujarla en pantalla (con el metodo dibujar)
   -Liberarla cuando ya no la necesito. (con el metodo liberar_recursos)

V 1.6: 02/11/2009
-Agrego las clases necesarias para reproducir sonidos.
-Para que SDL_Mixer funcione hay que tener el dll: mikmod.dll

V 1.5: 02/11/2009
-Agregue la clase CEntidad y la testeo con dos entidades "Bicho"
que mas adelante pueden ser cualquier entidad que yo necesite mostrar.
-Quite todo lo relacionado con el tateti.
-Quite todo lo relacionado con el bicho.

V 1.4: 02/11/2009
-Agregue la clase CAnimacion para controlar la animacion de un bicho.
-Comenté todo lo relacionado con el tateti.
-Mejoré los mensajes de error de SDL.

V 1.3: 01/11/2009
-Agregue codigo de prueba para aprender a gestionar otras cosas
y ahora el juego es un tateti jaja, quitar lo que no sirva...
- Meti todos los metodos de la clase CAplicacion dentro del
archivo CAplicacion.cpp
- Comenté bien todo lo que está hecho para el tateti para poder quitarlo
facilmente cuando sea necesario.

V 1.2: 01/11/2009
-Agregada la clase CEvento la cual es abstracta virtual y se encarga de
administrar de la mejor manera los eventos, cada vez que necesito responder
a un nuevo evento, en CAplicacion.h lo declaro como está declarado en
CEvento.h y luego en Manejar_Eventos.cpp lo defino con lo que necesito
que realize cuando se produce dicho evento.
-Agregué el manejador del evento que termina el programa cuando se presiona
Escape.
-Mejoré los nombres de los archivos que contienen los metodos de la clase
CAplicacion.
-Incluí comentarios en algunas rutinas.

V 1.1: 01/11/2009
-Agregada la clase CSuperficie que cargar imagenes y las coloca en la pantalla.
-Tambien esta sobrecargado el metodo dibujar para pegar en pantalla solo una
parte de la imagen cargada.

V 1.0: 01/11/2009
-Framework Basico funcional

*/
