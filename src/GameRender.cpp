#include "GameRender.hpp"

GameRender::GameRender(Grid g, vector<Tower> Towers, vector<Enemy> Enemys)
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
}
GameRender::~GameRender()
{
    if (towerTexture) SDL_DestroyTexture(towerTexture);
}

void GameRender::LoadTextures(SDL_Renderer* renderer)
{
    SDL_Surface* surface = SDL_LoadBMP("../sprites/tower1.bmp");
    if (!surface)
    {
        std::cerr << "Erreur chargement BMP tour: " << SDL_GetError() << std::endl;
        return;
    }

    // Rend transparente la couleur du pixel en haut à gauche (le "fond")
    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255); // adapte à la couleur de fond de ton BMP
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);

    towerTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
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
    SDL_Rect destRect = {
        static_cast<int>(t.cord.second * 100 + (100 - t.taille.first) / 2),
        static_cast<int>(t.cord.first * 100 + (100 - t.taille.second) / 2),
        static_cast<int>(t.taille.first),
        static_cast<int>(t.taille.second)};

    if (towerTexture)
    {
        SDL_RenderCopy(renderer, towerTexture, nullptr, &destRect);
    }
    else
    {
        // Repli si la texture n'a pas pu être chargée
        SDL_SetRenderDrawColor(renderer, 51, 0, 102, 255);
        SDL_RenderFillRect(renderer, &destRect);
    }
}

void GameRender::ProjectileRender(Projectile p, SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    float cx = (p.cord.second * 100 + (100 - p.taille.first) / 2);
    float cy = (p.cord.first * 100 + (100 - p.taille.second) / 2);
    float r = 10.0f;
    const float pas = 0.1f;
    float prevX = cx + r * cos(0.0f);
    float prevY = cy + r * sin(0.0f);

    for (float theta = pas; theta <= 2 * M_PI + pas; theta += pas)
    {
        float x = cx + r * cos(theta);
        float y = cy + r * sin(theta);

        SDL_RenderDrawLine(renderer,
                           static_cast<int>(prevX), static_cast<int>(prevY),
                           static_cast<int>(x), static_cast<int>(y));

        prevX = x;
        prevY = y;
    }
}

void GameRender::PlayerSelectRender(InputManager i, SDL_Renderer *renderer)
{
    SDL_Rect filledRect = {
        static_cast<int>(i.player.second * 100 + (100 - i.playerSize) / 2),
        static_cast<int>(i.player.first * 100 + (100 - i.playerSize) / 2),
        static_cast<int>(i.playerSize),
        static_cast<int>(i.playerSize)};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &filledRect);
}