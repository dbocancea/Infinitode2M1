#include "GameRender.hpp"

GameRender::GameRender(Grid g, vector <Tower> Towers , vector <Enemy> Enemys)
    : grid(g), Towers(Towers), Enemys(Enemys) {}

void GameRender::GridRender(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            SDL_Rect filledRect = {j * 100, i * 100, 100, 100};
            if (this->grid.map[i][j] == this->grid.mur)
            {

                SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }
            else if (this->grid.map[i][j] == this->grid.chemain)
            {

                SDL_SetRenderDrawColor(renderer, 189, 183, 107, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }
            else if (this->grid.map[i][j] == this->grid.tour)
            {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }
            else if (this->grid.map[i][j] == this->grid.arrive)
            {

                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }

            else if (this->grid.map[i][j] == this->grid.depart)
            {

                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void GameRender::EntityRender(Enemy e, SDL_Renderer *renderer)
{
    SDL_Rect filledRect = {
        static_cast<int>(e.cord.second * 100 + (100 - e.taille.first) / 2),
        static_cast<int>(e.cord.first * 100 + (100 - e.taille.second) / 2),
        static_cast<int>(e.taille.first),
        static_cast<int>(e.taille.second)};
    SDL_SetRenderDrawColor(renderer, 238, 130, 238, 255);
    SDL_RenderFillRect(renderer, &filledRect);
}

void GameRender::TowerRender(Tower t, SDL_Renderer *renderer)
{
    SDL_Rect filledRect = {
        static_cast<int>(t.cord.second * 100 + (100 - t.taille.first) / 2),
        static_cast<int>(t.cord.first * 100 + (100 - t.taille.second) / 2),
        static_cast<int>(t.taille.first),
        static_cast<int>(t.taille.second)};
    SDL_SetRenderDrawColor(renderer, 51, 0, 102, 255);
    SDL_RenderFillRect(renderer, &filledRect);
}

void GameRender::ProjectileRender( Projectile p , SDL_Renderer * renderer)
{
SDL_Rect filledRect = {
        static_cast<int>(p.cord.second * 100 + (100 - p.taille.first) / 2),
        static_cast<int>(p.cord.first * 100 + (100 - p.taille.second) / 2),
        static_cast<int>(p.taille.first),
        static_cast<int>(p.taille.second)};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &filledRect);
}