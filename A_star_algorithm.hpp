#ifndef A_STAR_ALGORITHM_HPP
#define A_STAR_ALGORITHM_HPP

#include <vector>
#include <SDL2/SDL.h>
#include "s.hpp"

struct Sector
{
  SDL_Point coord;
  float g_cost, h_cost;

  bool operator==(const Sector& s)
  {
    return (this->coord.x == s.coord.x && this->coord.y == s.coord.y);
  }
};
class A_star {
public:
  SDL_Point src, dist;
  int sector_size;
  bool run_flag;
  bool found_flag;
  std::vector<Sector> walked_sectors;
  std::vector<Sector> neighbour_sectors;


  A_star(unsigned int sector_size ,std::vector<SDL_Point*>* walls);
  void run();  
  void execuate(Snake *s);
  void set_src(SDL_Point p);
  void set_dist(SDL_Point h);
  float get_distance(SDL_Point a, SDL_Point b);
  Sector pop_closest_sector(std::vector<Sector> neighbour_sectors);
  void set_neighbour(Sector current);
  bool is_walked_sector(Sector sector);
  bool is_wall(Sector sector);
  float get_fcost(Sector s);

bool is_present(Sector sector);
  void delete_clone(Sector sector);
  void print_shit();
  void render_shit(SDL_Renderer* renderer);
 ~A_star();
};

#endif
