#ifndef GAMERENDER_HPP
#define GAMERENDER_HPP
#include <SDL.h>
#include "Grid.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include "Projectile.hpp"
#include "InputManager.hpp"
#include <vector>
#include <map>
class GameRender
{

public:
    map<char, array<int, 4>> color;
    Grid grid;
    vector<Tower> Towers;
    vector<Enemy> Enemys;
    SDL_Texture *towerTexture = nullptr;
    SDL_Texture *projectileTexture = nullptr;
    SDL_Texture *enemyTexture = nullptr;
    ~GameRender(); // <-- pour libérer la texture

    void LoadTextures(SDL_Renderer *renderer); // <-- nouveau
    GameRender(Grid g, vector<Tower> Towers, vector<Enemy> Enemys);
    void GridRender(SDL_Renderer *renderer);
    void EntityRender(Enemy e, SDL_Renderer *renderer);
    void TowerRender(Tower t, SDL_Renderer *renderer);
    void ProjectileRender(Projectile p, SDL_Renderer *renderer);
    void PlayerSelectRender(InputManager i, SDL_Renderer *renderer);
};

#endif