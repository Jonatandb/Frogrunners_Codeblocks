#include "CAnimacion.h"
CAnimacion::CAnimacion()
{
   CurrentFrame    = 0;
   MaxFrames       = 0;
   FrameInc        = 1;
   FrameRate       = 100; /// Milisegundos - Duración de cada fotograma.
   OldTime         = 0;
   Oscillate       = false;
}

void CAnimacion::Animar()
{
   if(OldTime + FrameRate > SDL_GetTicks())
   {
      return;
   }
   OldTime = SDL_GetTicks();

   CurrentFrame += FrameInc;

   if(Oscillate)
   {
      if(FrameInc > 0)
      {
         if(CurrentFrame >= MaxFrames - 1)
         {
            FrameInc = -FrameInc;
         }
      }else{
            if(CurrentFrame <= 0)
            {
               FrameInc = -FrameInc;
            }
      }
   }else{
         if(CurrentFrame >= MaxFrames)
         {
            CurrentFrame = 0;
         }
   }
}

void CAnimacion::SetFrameRate(int Rate)
{
   FrameRate = Rate; /// Milisegundos - Duración de cada fotograma.
}

void CAnimacion::SetCurrentFrame(int Frame)
{
   if(Frame < 0 || Frame >= MaxFrames) return;
   CurrentFrame = Frame;   /// Ir al fotograma especificado.
}

int CAnimacion::GetCurrentFrame()
{
   return CurrentFrame;  /// Devuelve el numero de fotoframa actual.
}
