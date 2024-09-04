#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <new>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <time.h>

#include "./window.hpp"
#include "./s.hpp"
#include "A_star_algorithm.hpp"

void render_grid(Window* window, int block_side);
void render_food(Window* window, Snake* snake, int block_side);
void render_snake(Window* window, Snake* snake);

int main()
{
  srand(time(0));
  int block_side = 50;

  Window* window = new Window("Snake", 720, 1080);
  Snake* snake = new Snake(block_side);
  A_star* algo = new A_star(block_side, nullptr);
  snake->generate_food();

  algo->src = snake->head[0];
  algo->dist = snake->food_coord;
  algo->run();

  SDL_Event e;
  bool running = true;
  int counter = 0;
  while(running)
  {
    if(SDL_PollEvent(&e) > 0)
    {
      if(e.type == SDL_QUIT) running = false;
      else
      {
        switch(e.key.keysym.sym)
        {
          case SDLK_w:
            snake->direction = 'w';
            break;
          case SDLK_s:
            snake->direction = 's';
            break;
          case SDLK_a:
            snake->direction = 'a';
            break;
          case SDLK_d:
            snake->direction = 'd';
            break;
        }
      }
    }
    render_grid(window, block_side);
    render_food(window, snake, block_side);
    render_snake(window, snake);

    counter++;
    if(counter == 1000)
    {
      snake->movement(snake->direction);
      algo->execuate(snake);

      printf("cycle one completed\n");
      if(snake->is_food_eaten()) 
      {
        snake->generate_food();
        algo->dist = snake->food_coord;
        algo->src = snake->head[0];
      }
      counter = 0;
    }

    window->render(window->window);
  }
  return 0;
}

void render_grid(Window* window, int block_side)
{
  SDL_SetRenderDrawColor(window->renderer, 0x00, 0x00, 0x00, 0xFF);
  for (int i = 0 ; i < window->height; i+=block_side) 
  {
    SDL_RenderDrawLine(window->renderer, 0, i, window->width, i);
  }
  for (int i = 0 ; i < window->width; i+=block_side) 
  {
    SDL_RenderDrawLine(window->renderer, i, 0, i, window->height);
  }
}

void render_food(Window* window, Snake* snake, int block_side)
{
    SDL_SetRenderDrawColor(window->renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Rect f = {snake->food_coord.x, snake->food_coord.y, block_side, block_side};
    SDL_RenderFillRect(window->renderer, &f);
}

void render_snake(Window* window, Snake* snake)
{
  SDL_SetRenderDrawColor(window->renderer, 0x6c, 0xd6, 0x3d, 0xFF);
  SDL_Rect p;
  for(int i = 0 ; i < snake->size ; ++i)
  {
    p = {snake->head[i].x, snake->head[i].y, snake->block_side, snake->block_side};
    SDL_RenderFillRect(window->renderer, &p);
  }
}