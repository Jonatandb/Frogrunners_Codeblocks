#ifndef _CANIMACION_H_
#define _CANIMACION_H_
#include <SDL.h>
class CAnimacion
{
   private:
            int   CurrentFrame;
            int   FrameInc;
            int   FrameRate; /// Milisegundos - Duración de cada fotograma.
            long  OldTime;
   public:
            CAnimacion();
            int   MaxFrames;
            bool  Oscillate;
            void  Animar();
            void  SetFrameRate(int Rate);
            void  SetCurrentFrame(int Frame);
            int   GetCurrentFrame();
};
#endif
