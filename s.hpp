#include <SDL2/SDL_rect.h>
#include <cstdio>
#include <cstdlib>
#include <vector>

class Snake
{
    private:


    public:
        std::vector<SDL_Point> head; 
        int size;
        int block_side;
        char direction;
        SDL_Point food_coord;
    
    Snake(int block_side) : size(1), direction('w')
    {
        this->block_side = block_side;
        head.push_back({(( rand() % 1080 ) / block_side ) * block_side, (( rand() % 720 ) / block_side ) * block_side});
    }
    bool collision_detection()
    {
        for(int i = 0 ; i < size ; ++i)
        {
            for(int j = 0 ; j < size ; ++j)
            {
                if(head[i].x == head[j].x && head[i].y == head[j].y) return true;
            }
        }
        return false;
    }
    bool collision_detection(SDL_Point p)
    {
       if(head[0].x == p.x && head[0].y == p.y)  
       {
         return true;
       }
       return false;
    }
    bool is_food_eaten()
    {
        if(head[0].x == food_coord.x && head[0].y == food_coord.y) 
        {
            this->size++;
            head.push_back({head[this->size].x , head[this->size].y - block_side});
            return true;
        }
        return false;
    }
    void movement(char dir)
    {
        direction = dir;
        switch (direction) 
        {
            case 'w':
                head.insert(head.begin() ,{head[0].x , head[0].y - block_side});
                break;
            case 'a':
                head.insert(head.begin() ,{head[0].x - block_side, head[0].y});
                break;
            case 'd':
                head.insert(head.begin() ,{head[0].x + block_side, head[0].y});
                break;
            case 's':
                head.insert(head.begin() ,{head[0].x , head[0].y + block_side});
                break;
        }
        head.pop_back();
        for(int i = 0 ; i < this->size ; ++i)
        {
            if(head[i].x > 1080) head[i].x = 0;
            if(head[i].x < 0) head[i].x = 1080;
            if(head[i].y > 720) head[i].y = 0;
            if(head[i].y < 0) head[i].y = 720;
        }

    }
    void generate_food()
    {
        food_coord.x = (( rand() % 1080 ) / block_side ) * block_side;
        food_coord.y = ((rand() % 720) / block_side ) * block_side;
    }
};