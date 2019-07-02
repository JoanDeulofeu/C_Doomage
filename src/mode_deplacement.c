#include "doom.h"

void  mode_deplacement(t_main *s)
{
  int   editor;

  editor = 1;
  while (editor)
  {
    while ((SDL_PollEvent(&(s->sdl->event))) != 0)
    {
      if (s->sdl->event.type ==  SDL_KEYDOWN)
      {
        if (s->sdl->event.key.keysym.sym == SDLK_v)
        {
          if (s->sdl->event.type == SDL_MOUSEMOTION && (s->sdl->event.motion.state & SDL_BUTTON_LEFT))
          {
            if (s->sdl->event.buttonx
          }
        }
      }
      else if (s->sdl->envent.type == SDL_QUIT)
        editor = 0;
    }

  }
}
