#include "CAplicacion.h"
#include <windows.h>
CAplicacion::CAplicacion() : musica("audios/musica.ogg")
{
   pantalla             = NULL; /// Superficie principal. Puntero inicializado.
   funcionando          = true;   /// FUNCIONANDO ?
   mostrar_presentacion = false;   /// PRESENTACION ?
   menu_visible         = true;   /// MENU ? (No modificar!)
   dibujar_menu         = true;
   menu_opciones_visible= true;   /// MENU OPCIONES ?
   dibujar_menu_opciones= false;
   juego_visible        = false;   /// JUEGO ?
   dibujar_juego        = false;
   actualizar_musica    = false;   /// MUSICA ?
   musica_activa        = false;
   sonido_activo        = false;    /// SONIDO ?
   pantalla_completa    = false;   /// PANTALLA
   actualizar_pantalla  = false;
   SDL_EnableKeyRepeat(30, 30);
}

int CAplicacion::Ejecutar()
{
   if(Inicializacion() == false)
   {
      cerr << "No se pudo realizar la incializacion de la aplicación... :( " << SDL_GetError() << endl;
      return -1;
   }
   Presentacion();
   while(funcionando)
   {
      Menu_Principal();
      Menu_Opciones();
      Juego();
      while(SDL_PollEvent(&Event))
      {
         Manejar_Eventos(&Event);
      }
      Hacer_Calculos();
      Dibujar();
   }
   Liberar_Recursos();
   return 0;
}

bool CAplicacion::Inicializacion()
{
   cout << "Frogrunners | -.Jonatandb.-" << endl << endl;
   cout << "Reporte de funcionamiento:" << endl << endl;

   if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
   {
      cerr << "SDL no se pudo iniciar... :( " << SDL_GetError() << endl;
      return false;
   }
   cout << "SDL se inicio bien :)" << endl;

   if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS, 4096) < 0)
   {
      cerr << "El Sonido no se pudo iniciar... :( " << SDL_GetError() << endl;
      return false;
   }
   cout << "El sonido se inicio bien :)" << endl;
   cout << "La musica se cargo bien :)" << endl;
   SDL_Surface *icono = SDL_LoadBMP("imagenes/icono.bmp");
   if(icono==NULL)
   {
      cerr << "El icono no se pudo cargar... :( " << SDL_GetError() << endl;
      return false;
   }
   cout << "El icono se cargo bien :)" << endl;

   SDL_WM_SetCaption("Frogrunners | -.Jonatandb.-",NULL);
   cout << "El titulo se seteo bien :)" << endl;
   SDL_WM_SetIcon(icono, NULL);
   SDL_ShowCursor(0);
   if(pantalla_completa)
   {
      if((pantalla = SDL_SetVideoMode(ANCHO_VENTANA, ALTO_VENTANA, 32, SDL_HWSURFACE | SDL_DOUBLEBUF|SDL_FULLSCREEN)) == NULL)
      {
         cerr << "El modo de video no se pudo setear... :( " << SDL_GetError() << endl;
         funcionando = false;
      }
   }else{
         if((pantalla = SDL_SetVideoMode(ANCHO_VENTANA, ALTO_VENTANA, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
         {
            cerr << "El modo de video no se pudo setear... :( " << SDL_GetError() << endl;
            funcionando = false;
         }
   }
   cout << "El video se seteo bien :)" << endl;

   SDL_FreeSurface(icono); /// Libero el icono, ya no lo necesito.

   if( (sonido_opcion_elegida = CSonido::ControlSonido.Cargar("audios/opcion_elegida.wav")) == -1)
   {
      cerr << "El Sonido no se pudo cargar... :( " << SDL_GetError() << endl;
   }

   if(rana1.Cargar("imagenes/rana.png",150,150,1) == false)
   {
      cerr << "La Rana no se pudo cargar... :( " << SDL_GetError() << endl;
   }
   rana1.X = 295;
   rana1.Y = 430;
   CSuperficie::Transparente(rana1.Sup_Entidad,0,0,0);
   CEntidad::ListaEntidades.push_back(&rana1);

   cout << "La inicializacion fue exitosa :)" << endl << endl;

   return true;
}

void CAplicacion::Presentacion()
{
   if(mostrar_presentacion)
   {
      SDL_Surface *presentacion;
      SDL_Rect destino;
      destino.x=0;
      destino.y=0;
      destino.h=0;
      destino.w=0;
      presentacion = IMG_Load("imagenes/presentacion.png");
      if(presentacion==NULL)
      {
         cerr << "No se pudo cargar la imagen... :( " << SDL_GetError() << endl;
         funcionando=false;
      }
      cout << "La presentacion se cargo bien :)" << endl;
      SDL_Surface *tmp = presentacion;
      presentacion = SDL_DisplayFormat(tmp);
      SDL_FreeSurface(tmp);
      int i=0;
      Uint32 negro = SDL_MapRGB(pantalla->format, 0, 0, 0);
      SDL_Delay(2000);
      for(i=0;i<15;i++)
      {
         SDL_SetAlpha(presentacion, SDL_SRCALPHA|SDL_RLEACCEL, i*17);
         SDL_BlitSurface(presentacion,NULL,pantalla,&destino);
         SDL_Flip(pantalla);
         SDL_Delay(50);
         SDL_FillRect(pantalla, NULL, negro);
      }
      SDL_Delay(2000); /// Pausa para ver la presentacion.
      for(i=15;i>0;i--)
      {
         SDL_SetAlpha(presentacion, SDL_SRCALPHA|SDL_RLEACCEL, i*17);
         SDL_BlitSurface(presentacion,NULL,pantalla,&destino);
         SDL_Flip(pantalla);
         SDL_Delay(50);
         SDL_FillRect(pantalla, NULL, negro);
      }
      SDL_FreeSurface(presentacion);
      mostrar_presentacion = false;   /// se desactiva la presentacion asi no se redibuja.
   }
   SDL_ShowCursor(1);
   SDL_WarpMouse(ANCHO_VENTANA/2,ALTO_VENTANA/2);
   actualizar_musica=true;
}

void CAplicacion::Menu_Principal()
{
   if(menu_visible && dibujar_menu)
   {
      SDL_Surface *menu;
      SDL_Rect destino;
      destino.x=0;   destino.y=0;   destino.h=0;   destino.w=0;
      menu = IMG_Load("imagenes/menu_principal.png");
      if(menu==NULL)
      {
         cerr << "No se pudo cargar la imagen... :( " << SDL_GetError() << endl;
         funcionando=false;
      }
      SDL_Surface *tmp = menu;
      menu = SDL_DisplayFormat(tmp);
      SDL_FreeSurface(tmp);
      SDL_BlitSurface(menu,NULL,pantalla,&destino);
      dibujar_menu=false;
      SDL_FreeSurface(menu);
   }
}

void CAplicacion::Juego()
{
   if(juego_visible && dibujar_juego)
   {
      SDL_Surface *fondo;
      SDL_Rect destino;
      destino.x=0;   destino.y=0;   destino.h=0;   destino.w=0;
      fondo = IMG_Load("imagenes/fondo_juego1.png");
      if(fondo==NULL)
      {
         cerr << "No se pudo cargar la imagen... :( " << SDL_GetError() << endl;
         funcionando=false;
      }
      SDL_Surface *tmp = fondo;
      fondo = SDL_DisplayFormat(tmp);
      SDL_FreeSurface(tmp);
      SDL_BlitSurface(fondo,NULL,pantalla,&destino);
      cout << "Se inicio el juego, se mostro bien :)" << endl;
      dibujar_juego=false;
      SDL_FreeSurface(fondo);
   }
}

void CAplicacion::Menu_Opciones()
{
   if(menu_opciones_visible && dibujar_menu_opciones)
   {
      SDL_Surface *opciones;
      SDL_Rect destino;
      destino.x=0;   destino.y=0;   destino.h=0;   destino.w=0;
      opciones = IMG_Load("imagenes/menu_opciones.png");
      if(opciones==NULL)
      {
         cerr << "No se pudo cargar la imagen... :( " << SDL_GetError() << endl;
         funcionando=false;
      }
      SDL_Surface *tmp = opciones;
      opciones = SDL_DisplayFormat(tmp);
      SDL_FreeSurface(tmp);
      SDL_BlitSurface(opciones,NULL,pantalla,&destino);
      dibujar_menu_opciones=false;
      SDL_FreeSurface(opciones);
   }
}

void CAplicacion::Manejar_Eventos(SDL_Event* Evento)
{
   CEvento::OnEvent(Evento);
}

void CAplicacion::Hacer_Calculos()
{
   if(actualizar_musica)
   {
      if(musica_activa)
      {
         musica.reproducir();
         actualizar_musica=false;
      }else{
            musica.pausar();
            actualizar_musica=false;
      }
   }
   SDL_Delay(10);  /// Disminuyo el uso de cpu a la mitad sin notarlo en mi juego.
}

void CAplicacion::Dibujar()
{
   if(actualizar_pantalla)
   {
      if(pantalla_completa)
      {
         if((pantalla = SDL_SetVideoMode(ANCHO_VENTANA, ALTO_VENTANA, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN)) == NULL)
         {
            cerr << "El modo de video no se pudo setear... :( " << SDL_GetError() << endl;
            funcionando = false;
         }
         actualizar_pantalla = false;
      }else{
            if((pantalla = SDL_SetVideoMode(ANCHO_VENTANA, ALTO_VENTANA, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL)
            {
               cerr << "El modo de video no se pudo setear... :( " << SDL_GetError() << endl;
               funcionando = false;
            }
            actualizar_pantalla = false;
      }
   }

   if(juego_visible) rana1.Dibujar(pantalla);
   SDL_Flip(pantalla); /// Actualizo la pantalla con todo lo que le dibujé.
}

void CAplicacion::Liberar_Recursos()
{
   cout << endl;
   cout << "Reporte de liberacion de recursos:" << endl << endl;
   SDL_FreeSurface(pantalla);
   cout << "Memoria asignada a la pantalla, liberada :)" << endl;

   CSonido::ControlSonido.Liberar_Recursos();

   Mix_CloseAudio();

   SDL_Quit();
   cout << "SDL cerrado correctamente :)" << endl;

}

void CAplicacion::Salir()
{
   funcionando = false;
}

void CAplicacion::TeclaPresionada(SDLKey sym, SDLMod mod, Uint16 unicode)
{
   if(sym==SDLK_ESCAPE)
   {
      if(menu_visible)
      {
         if(pantalla_completa)
         {
            if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
            SDL_WarpMouse(ANCHO_VENTANA/2,ALTO_VENTANA/2);
            pantalla_completa=false;
            actualizar_pantalla=true;
            dibujar_menu=true;
         }else{
               SDL_ShowCursor(0);
               funcionando = false;
         }
      }
      if(menu_opciones_visible)
      {
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
         menu_opciones_visible=false;
         dibujar_menu_opciones=false;
         menu_visible=true;
         dibujar_menu=true;
      }
      if(juego_visible)
      {
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
         juego_visible=false;
         dibujar_juego=false;
         menu_visible=true;
         dibujar_menu=true;
         SDL_ShowCursor(1);
         SDL_WarpMouse(ANCHO_VENTANA/2,ALTO_VENTANA/2);
      }
   }
   if(juego_visible)
   {
      if(sym==SDLK_UP)
      {
         rana1.Y-=35;
         if(rana1.Y<=0) rana1.Y=0;
         dibujar_juego=true;
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
      }
      if(sym==SDLK_DOWN)
      {
         rana1.Y+=35;
         if(rana1.Y>=430) rana1.Y=430;
         dibujar_juego=true;
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
      }
   }
}

void CAplicacion::BotonIzqMousePresionado(int mX, int mY)
{
   /// no hago nada
}

void CAplicacion::BotonIzqMouseSoltado(int mX, int mY)
{
   if(menu_visible)
   {
      SDL_ShowCursor(1);
      ///* Click en comenzar.
      if(  ((mX>201)&&(mX<424)) && ((mY>108)&&(mY<236)) )
      {
         menu_visible=false; /// oculto el menu.
         dibujar_menu=false;
         SDL_ShowCursor(0);  /// oculto el cursor.
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
         juego_visible=true;
         dibujar_juego=true;
         cout << "Se hizo click en comenzar :)" << endl;
      }
      ///* Click en opciones
      if(  ((mX>199)&&(mX<421)) && ((mY>239)&&(mY<301)) )
      {
         menu_visible=false; /// oculto el menu principal.
         menu_opciones_visible=true;
         dibujar_menu_opciones=true;
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
      }
      ///* Click en ranking
      if(  ((mX>214)&&(mX<416)) && ((mY>309)&&(mY<371)) )
      {
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
         ///**** HACER!
         cout << "El Ranking aun no fue implementado... :(" << endl;
      }
      ///* Click en salir.
      if(  ((mX>254)&&(mX<366)) && ((mY>369)&&(mY<421)) )
      {
         cout << "Se clickeo en salir :(" << endl;
         funcionando=false;
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
      }
      ///* Click en mi web.
      if(  ((mX>190)&&(mX<451)) && ((mY>427)&&(mY<474)) )
      {
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
         ShellExecute( NULL, "open", "http://www.jonatandb.com.ar", NULL, NULL, 0 );
      }
   }
   if(menu_opciones_visible)
   {
      SDL_ShowCursor(1);
      ///* Click en pantalla completa.
      if( ((mX>240)&&(mX<637)) && ((mY>175)&&(mY<237)) )
      {
         pantalla_completa=!pantalla_completa;
         actualizar_pantalla=true;
         dibujar_menu_opciones=true;
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
      }
      ///* Click en sonido.
      if( (mX>456 && mX<638) && (mY>236 && mY<298) )
      {
         sonido_activo=!sonido_activo;
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
      }
      ///* Click en música.
      if( (mX>458 && mX<640) && (mY>304&& mY<366) )
      {
         actualizar_musica=true;
         musica_activa=!musica_activa;
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
      }
      ///* Click en configurar teclas.
      if( (mX>260 && mX<637) && (mY>369&& mY<434) )
      {
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
         ///**** HACER!
         cout << "La Configuracion de teclas aun no fue implementada... :(" << endl;
      }
      ///* Click en mi web.
      if(  ((mX>190)&&(mX<451)) && ((mY>427)&&(mY<474)) )
      {
         if(sonido_activo) CSonido::ControlSonido.Reproducir(sonido_opcion_elegida);
         ShellExecute( NULL, "open", "http://www.jonatandb.com.ar", NULL, NULL, 0 );
      }
   }
}

