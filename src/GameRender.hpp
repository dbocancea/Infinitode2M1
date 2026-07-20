#ifndef GAMERENDER_HPP
#define GAMERENDER_HPP

#include "Grid.hpp"
#include "Entity.hpp"
#include <vector>
class GameRender
{

public:
    Grid grid;
    vector <Entity> Towers;
    vector <Entity> Enemys;
    GameRender(Grid g , vector <Entity> Towers , vector <Entity> Enemys);
    void GridRender();
    void EntityRender(Entity e);
};

#endif