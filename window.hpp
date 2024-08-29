#include <SDL2/SDL.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_shape.h>
#include <SDL2/SDL_video.h>
#include <cstddef>

class Window 
{
  private:

  public:
    int height;
    int width;
    SDL_Color color;

    SDL_Window* window;
    SDL_Renderer* renderer;



    Window(const char* window_title, const int height, const int width)
    {
      if(SDL_Init(SDL_INIT_VIDEO) < 0) return;

      SDL_Window* window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
      if(window == nullptr) 
      {
        SDL_Quit();
        return;
      }

      this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      if(this->renderer == nullptr)
      {
        Shutdown(window, renderer);
      }
      this->height = height;
      this->width = width;
      return;
    }

    void render(SDL_Window* window)
    {
      SDL_SetRenderDrawColor(this->renderer, 0x00, 0x00, 0x00, 0x00);
      SDL_RenderPresent(this->renderer);
      SDL_RenderClear(this->renderer);
    }

    void Shutdown(SDL_Window* window, SDL_Renderer* renderer)
    {
    if (window != nullptr) {
      SDL_DestroyWindow(window);
      window = nullptr;
    }

    if (renderer != nullptr) {
      SDL_DestroyRenderer(renderer);
      renderer = nullptr;
    }

    SDL_Quit();
    }

};


