#include "A_star_algorithm.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdio>

A_star::A_star(unsigned int sector_size ,std::vector<SDL_Point*>* walls) 
{
  this->sector_size = sector_size;
  this->run_flag = false;
  found_flag = false;
}

void A_star::run()
{
  run_flag = true;
  neighbour_sectors.push_back({this->src, 9999.0f, get_distance(this->src, this->dist)});
  printf("shit set\n");
}

void A_star::execuate(Snake *s)
{
  if(found_flag) return;
  if(!run_flag) run();
  Sector current = pop_closest_sector(this->neighbour_sectors); 
  // shit code begains here
printf("aaacycle one completed\n");

  if(current.coord.x == s->head[0].x && current.coord.y == s->head[0].y - sector_size)
  {
    s->movement('w');
  }
  else if (current.coord.x == s->head[0].x - sector_size && current.coord.y == s->head[0].y)
  {
    s->movement('a');
  }
  else if (current.coord.x == s->head[0].x + sector_size && current.coord.y == s->head[0].y) 
  {
    s->movement('d');
  }
  else if(current.coord.x == s->head[0].x && current.coord.y == s->head[0].y + sector_size)
  {
    s->movement('s');
  }
  else if(current.coord.x == s->head[0].x - sector_size && current.coord.y == s->head[0].y - sector_size)
  {
    s->movement('s');
    s->movement('w');
  }
  else if(current.coord.x == s->head[0].x + sector_size && current.coord.y == s->head[0].y - sector_size)
  {
    s->movement('d');
    s->movement('w');
  }
  else if (current.coord.x == s->head[0].x - sector_size && current.coord.y == s->head[0].y + sector_size) {
    s->movement('s');
    s->movement('a');
  }
  else if(current.coord.x == s->head[0].x + sector_size && current.coord.y == s->head[0].y + sector_size)
  {
    s->movement('d');
    s->movement('s');
  }

  if(current.coord.x == dist.x && current.coord.y == dist.y) {found_flag = true; return;}
  set_neighbour(current);

}

void A_star::set_src(SDL_Point p)
{
  this->src = p;
}

void A_star::set_dist(SDL_Point h)
{
  this->dist = h;
}

void A_star::set_neighbour(Sector current)
{
  Sector temp = current;
  for(int i= 0 ; i < 8 ; ++i)
  {
    temp = current;
    switch (i) 
    {
      case 0:
        temp.coord.x-=sector_size;
        temp.coord.y-=sector_size;
        break;
      case 1:
        temp.coord.y-=sector_size;
        break;
      case 2:
        temp.coord.x+=sector_size;
        temp.coord.y-=sector_size;       
        break;
      case 3:
        temp.coord.x-=sector_size;
        break;
      case 4:
        temp.coord.x+=sector_size;
        break;
      case 5:
        temp.coord.x-=sector_size;
        temp.coord.y+=sector_size;
        break;
      case 6:
        temp.coord.y+=sector_size;
        break;
      case 7:
        temp.coord.x+=sector_size;
        temp.coord.y+=sector_size;
        break;
    }

      temp.g_cost = get_distance(temp.coord, src);
      temp.h_cost = get_distance(temp.coord, dist);
      if(!is_present(temp))
      {
        neighbour_sectors.push_back(temp);    
      }
    }
  
  print_shit();
}


bool A_star::is_present(Sector sector)
{
  for(auto s : neighbour_sectors)
  {
    if(sector == s) return true;
  }
  return false;
}



Sector A_star::pop_closest_sector(std::vector<Sector> neighbour_sectors)
{
  int index_closest_sector = 0;
  for(size_t i = 0 ; i < neighbour_sectors.size() ; ++i)
  {
    if(get_fcost(neighbour_sectors[i]) <= get_fcost(neighbour_sectors[index_closest_sector]))
    {
      index_closest_sector = i;
    }
  }

  Sector s = neighbour_sectors[index_closest_sector];
  printf("poped %d %d = %f\n", s.coord.x, s.coord.y, s.h_cost+s.g_cost);
  delete_clone(s);

  return s;
}

float A_star::get_fcost(Sector s)
{
  return s.h_cost+s.g_cost;
}

float A_star::get_distance(SDL_Point a, SDL_Point b)
{
  float dx = b.x - a.x;
  float dy = b.y - a.y;

  return sqrt((dx*dx) + (dy*dy));
}



void A_star::delete_clone(Sector sector)
{
  for(int i = 0 ; i < neighbour_sectors.size() ; ++i)
  {
      neighbour_sectors.erase(std::find(neighbour_sectors.begin(), neighbour_sectors.end(), sector));
  }
}

void A_star::print_shit()
{
  for(auto temp : neighbour_sectors)
  {
      printf("new neighbour_sectors: %d %d = %f\n",temp.coord.x, temp.coord.y ,temp.h_cost+temp.g_cost);
  }
}

A_star::~A_star() 
{

}
