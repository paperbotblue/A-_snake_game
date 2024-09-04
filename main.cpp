#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <new>
#include <iostream>
#include <SDL2/SDL.h>
#include <time.h>
#include <vector>

#include "./window.hpp"
#include "./s.hpp"

#define PRINT(x) std::cout << x << "\n"


struct Sector
{
  SDL_Point coord;
  float distance;

  bool operator==(const Sector& s)
  {
    return (this->coord.x == s.coord.x && this->coord.y == s.coord.y);
  }
};

void render_grid(Window* window, int block_side);
void render_food(Window* window, Snake* snake, int block_side);
void render_snake(Window* window, Snake* snake);
void set_neighbour(SDL_Point p,int block_side, SDL_Point food_coord , std::vector<Sector>* neighbours);
float get_distance(SDL_Point a, SDL_Point b);
int pop_closest_sector(Snake* s,std::vector<Sector>* neighbours);

int main()
{
  srand(time(0));
  int block_side = 50;

  Window* window = new Window("Snake", 750, 1100);
  Snake* snake = new Snake(block_side);
  std::vector<Sector>* neighbours = new std::vector<Sector>;

  snake->generate_food();
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
      set_neighbour(snake->head[0], block_side ,snake->food_coord ,neighbours);
      switch (pop_closest_sector(snake ,neighbours)) 
      {
        case 0:
          snake->movement('w');
          break;
        case 1:
         snake->movement('s');
          break;
        case 2:
         snake->movement('d'); 
          break;
        case 3:
          snake->movement('a');
          break;
      }
      neighbours->clear();
      if(snake->is_food_eaten()) snake->generate_food();
      counter = 0;
    }

    window->render(window->window);
  }
  return 0;
}

void set_neighbour(SDL_Point p,int block_side ,SDL_Point food_coord, std::vector<Sector>* neighbours)
{ 
  neighbours->push_back({{p.x , p.y - block_side}, 0});
  neighbours->at(0).distance = get_distance(neighbours->at(0).coord, food_coord );

  PRINT(neighbours->at(0).distance);

  neighbours->push_back({{p.x , p.y + block_side}, 0});
  neighbours->at(1).distance = get_distance(neighbours->at(1).coord, food_coord );

  PRINT(neighbours->at(1).distance);
  neighbours->push_back({{p.x + block_side , p.y}, 0});
  neighbours->at(2).distance = get_distance(neighbours->at(2).coord, food_coord );

  PRINT(neighbours->at(2).distance);
  neighbours->push_back({{p.x - block_side , p.y}, 0});
  neighbours->at(3).distance = get_distance(neighbours->at(3).coord, food_coord );
  PRINT(neighbours->at(3).distance);
}

int pop_closest_sector( Snake* s,std::vector<Sector>* neighbours)
{
  int closest_sector = 0;
  for(int i = 1 ; i < neighbours->size() ; ++i)
  {
    if(neighbours->at(i).distance < neighbours->at(closest_sector).distance)
    {
      if(s->collision_detection(neighbours->at(i).coord))
      {
        continue;
      }
      closest_sector = i;
    }
  }
  PRINT(neighbours->at(closest_sector).distance << "  " << closest_sector);
  return closest_sector;
}

float get_distance(SDL_Point a, SDL_Point b)
{
  float dx = b.x - a.x;
  float dy = b.y - a.y;

  return sqrt((dx*dx) + (dy*dy));
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