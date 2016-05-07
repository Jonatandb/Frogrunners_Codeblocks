#include "CEvento.h"

CEvento::CEvento()
{
   /// Constructor por defecto
}

CEvento::~CEvento()
{
   /// Destructor que no hace nada.
}

void CEvento::OnEvent(SDL_Event* Event)
{
   switch(Event->type)
   {
      case SDL_ACTIVEEVENT:
      {
         switch(Event->active.state)
         {
            case SDL_APPMOUSEFOCUS:
            {
               if ( Event->active.gain )
               {
                  OnMouseFocus();
               }else{
                     OnMouseBlur();
               }
               break;
            }
            case SDL_APPINPUTFOCUS:
            {
               if ( Event->active.gain )
               {
                  OnInputFocus();
               }else{
                     OnInputBlur();
               }
               break;
            }
            case SDL_APPACTIVE:
            {
               if ( Event->active.gain )
               {
                  OnRestore();
               }else{
                     OnMinimize();
               }
               break;
            }
         }
         break;
      }
      case SDL_KEYDOWN:
      {
         TeclaPresionada(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
         break;
      }
      case SDL_KEYUP:
      {
         TeclaSoltada(Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
         break;
      }
      case SDL_MOUSEMOTION:
      {
         OnMouseMove(Event->motion.x, Event->motion.y, Event->motion.xrel, Event->motion.yrel,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(Event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
         break;
      }
      case SDL_MOUSEBUTTONDOWN:
      {
         switch(Event->button.button)
         {
            case SDL_BUTTON_LEFT:
            {
               BotonIzqMousePresionado(Event->button.x,Event->button.y);
               break;
            }
            case SDL_BUTTON_RIGHT:
            {
               OnRButtonDown(Event->button.x,Event->button.y);
               break;
            }
            case SDL_BUTTON_MIDDLE:
            {
               OnMButtonDown(Event->button.x,Event->button.y);
               break;
            }
         }
         break;
      }
      case SDL_MOUSEBUTTONUP:
      {
         switch(Event->button.button)
         {
            case SDL_BUTTON_LEFT:
            {
               BotonIzqMouseSoltado(Event->button.x,Event->button.y);
               break;
            }
            case SDL_BUTTON_RIGHT:
            {
               OnRButtonUp(Event->button.x,Event->button.y);
               break;
            }
            case SDL_BUTTON_MIDDLE:
            {
               OnMButtonUp(Event->button.x,Event->button.y);
               break;
            }
         }
         break;
      }
      case SDL_JOYAXISMOTION:
      {
         OnJoyAxis(Event->jaxis.which,Event->jaxis.axis,Event->jaxis.value);
         break;
      }
      case SDL_JOYBALLMOTION:
      {
         OnJoyBall(Event->jball.which,Event->jball.ball,Event->jball.xrel,Event->jball.yrel);
         break;
      }
      case SDL_JOYHATMOTION:
      {
         OnJoyHat(Event->jhat.which,Event->jhat.hat,Event->jhat.value);
         break;
      }
      case SDL_JOYBUTTONDOWN:
      {
         OnJoyButtonDown(Event->jbutton.which,Event->jbutton.button);
         break;
      }
      case SDL_JOYBUTTONUP:
      {
         OnJoyButtonUp(Event->jbutton.which,Event->jbutton.button);
         break;
      }
      case SDL_QUIT:
      {
         Salir();
         break;
      }
      case SDL_SYSWMEVENT:
      {
         // Se ignora por su complejidad de manejo.
         break;
      }
      case SDL_VIDEORESIZE:
      {
         OnResize(Event->resize.w,Event->resize.h);
         break;
      }
      case SDL_VIDEOEXPOSE:
      {
         OnExpose();
         break;
      }
      default:
      {
         OnUser(Event->user.type,Event->user.code,Event->user.data1,Event->user.data2);
      break;
      }
   }
}

void CEvento::OnInputFocus() {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnInputBlur() {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::TeclaPresionada(SDLKey sym, SDLMod mod, Uint16 unicode) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::TeclaSoltada(SDLKey sym, SDLMod mod, Uint16 unicode) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnMouseFocus() {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnMouseBlur() {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnMouseWheel(bool Up, bool Down) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::BotonIzqMousePresionado(int mX, int mY) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::BotonIzqMouseSoltado(int mX, int mY) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnRButtonDown(int mX, int mY) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnRButtonUp(int mX, int mY) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnMButtonDown(int mX, int mY) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnMButtonUp(int mX, int mY) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnJoyAxis(Uint8 which,Uint8 axis,Sint16 value) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnJoyButtonDown(Uint8 which,Uint8 button) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnJoyButtonUp(Uint8 which,Uint8 button) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnJoyHat(Uint8 which,Uint8 hat,Uint8 value) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnJoyBall(Uint8 which,Uint8 ball,Sint16 xrel,Sint16 yrel) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnMinimize() {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnRestore() {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnResize(int w,int h) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnExpose() {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::Salir() {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
void CEvento::OnUser(Uint8 type, int code, void* data1, void* data2) {
   /// Metodo virtual, lo sobreescribe quien lo necesite luego de heredarlo.
}
