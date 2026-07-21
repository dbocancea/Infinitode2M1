#ifndef GAMERENDER_HPP
#define GAMERENDER_HPP
#include<SDL.h>
#include "Grid.hpp"
#include "Enemy.hpp"
#include <vector>
#include <map>
class GameRender
{

public:
    map <char , array<int,4> > color;
    Grid grid;
    vector <Entity> Towers;
    vector <Entity> Enemys;
    GameRender(Grid g , vector <Entity> Towers , vector <Entity> Enemys);
    void GridRender(SDL_Renderer* renderer);
    void EntityRender(Enemy e , SDL_Renderer* renderer);
};

#endif