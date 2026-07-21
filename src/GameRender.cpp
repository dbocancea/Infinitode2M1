#include "GameRender.hpp"

GameRender::GameRender(Grid g, std::vector<Entity> Towers, std::vector<Entity> Enemys)
    : grid(g), Towers(Towers), Enemys(Enemys) {}

void GameRender::GridRender(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    for( int i = 0; i < 10 ; i++  )
    {
        for( int j = 0; j < 10 ; j++  )
        {
            SDL_Rect filledRect = { j*100, i*100, 100, 100 };
            if(this->grid.map[i][j] == this->grid.mur)
            {
                
                SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }
            else
            if(this->grid.map[i][j] == this->grid.chemain)
            {
               
                SDL_SetRenderDrawColor(renderer, 189, 183, 107, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }
            else
            if(this->grid.map[i][j] == this->grid.tour)
            {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }
            else
            if(this->grid.map[i][j] == this->grid.arrive)
            {
               
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }

            else
            if(this->grid.map[i][j] == this->grid.depart)
            {
            
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }
           
        }
    }
     SDL_RenderPresent(renderer);
}

void GameRender::EntityRender(Enemy e , SDL_Renderer* renderer)
{
   SDL_Rect filledRect = {
        static_cast<int>(e.cord.second * 100+25),
        static_cast<int>(e.cord.first * 100+25),
        static_cast<int>(e.taille.first),
        static_cast<int>(e.taille.second)};    
        SDL_SetRenderDrawColor(renderer, 238, 130, 238, 255);
    SDL_RenderFillRect(renderer, &filledRect);
}