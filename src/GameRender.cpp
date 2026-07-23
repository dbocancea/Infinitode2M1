#include "GameRender.hpp"

GameRender::GameRender(Grid g, vector<Tower> Towers, vector<Enemy> Enemys)
    : grid(g), Towers(Towers), Enemys(Enemys) {}

static void DrawThickRect(SDL_Renderer *renderer, const SDL_Rect &rect, int thickness)
{
    SDL_Rect top    = { rect.x, rect.y, rect.w, thickness };
    SDL_Rect bottom = { rect.x, rect.y + rect.h - thickness, rect.w, thickness };
    SDL_Rect left   = { rect.x, rect.y, thickness, rect.h };
    SDL_Rect right  = { rect.x + rect.w - thickness, rect.y, thickness, rect.h };
 
    SDL_RenderFillRect(renderer, &top);
    SDL_RenderFillRect(renderer, &bottom);
    SDL_RenderFillRect(renderer, &left);
    SDL_RenderFillRect(renderer, &right);
}


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

                SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
                SDL_RenderFillRect(renderer, &filledRect);
                continue;
            }
            else if (this->grid.map[i][j] == this->grid.chemain)
            {

                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }
            else if (this->grid.map[i][j] == this->grid.tour)
            {
                SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }
            else if (this->grid.map[i][j] == this->grid.arrive)
            {

                SDL_SetRenderDrawColor(renderer, 211, 47, 47, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }

            else if (this->grid.map[i][j] == this->grid.depart)
            {

                SDL_SetRenderDrawColor(renderer, 30, 90, 200, 255);
                SDL_RenderFillRect(renderer, &filledRect);
            }
            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
            DrawThickRect(renderer, filledRect, 3);
        }
    }
}

GameRender::~GameRender()
{
    if (towerTexture)
        SDL_DestroyTexture(towerTexture);
}

void GameRender::LoadTextures(SDL_Renderer *renderer)
{
    SDL_Surface *surface = SDL_LoadBMP("../sprites/tower1.bmp");
    if (!surface)
    {
        std::cerr << "Erreur chargement BMP tour: " << SDL_GetError() << std::endl;
        return;
    }

    Uint32 colorKey = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);

    towerTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Surface *surface1 = SDL_LoadBMP("../sprites/enemy.bmp");
    if (!surface1)
    {
        std::cerr << "Erreur chargement BMP enemy: " << SDL_GetError() << std::endl;
        return;
    }

    Uint32 colorKey1 = SDL_MapRGB(surface1->format, 255, 255, 255);
    SDL_SetColorKey(surface1, SDL_TRUE, colorKey1);

    enemyTexture = SDL_CreateTextureFromSurface(renderer, surface1);

    SDL_FreeSurface(surface1);

    SDL_Surface *surface2 = SDL_LoadBMP("../sprites/projectile.bmp");
    if (!surface2)
    {
        std::cerr << "Erreur chargement BMP enemy: " << SDL_GetError() << std::endl;
        return;
    }

    Uint32 colorKey2 = SDL_MapRGB(surface2->format, 255, 255, 255);
    SDL_SetColorKey(surface2, SDL_TRUE, colorKey2);

    projectileTexture = SDL_CreateTextureFromSurface(renderer, surface2);

    SDL_FreeSurface(surface2);
}

void GameRender::EntityRender(Enemy e, SDL_Renderer *renderer)
{
    SDL_Rect filledRect = {
        static_cast<int>(e.cord.second * 100 + (100 - e.taille.first) / 2),
        static_cast<int>(e.cord.first * 100 + (100 - e.taille.second) / 2),
        static_cast<int>(e.taille.first),
        static_cast<int>(e.taille.second)};
    if (enemyTexture)
    {
        SDL_RenderCopy(renderer, enemyTexture, nullptr, &filledRect);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 238, 130, 238, 255);
        SDL_RenderFillRect(renderer, &filledRect);
    }
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
        int row = static_cast<int>(t.cord.first);
        int col = static_cast<int>(t.cord.second);

        double angle = 0.0;

        bool bas = (row + 1 < 10 && this->grid.map[row + 1][col] == this->grid.chemain);
        bool droite = (col + 1 < 10 && this->grid.map[row][col + 1] == this->grid.chemain);
        bool gauche = (col - 1 >= 0 && this->grid.map[row][col - 1] == this->grid.chemain);

        if (bas)
            angle = 180.0;
        else if (droite)
            angle = 90.0;
        else if (gauche)
            angle = -90.0;

        SDL_RenderCopyEx(renderer, towerTexture, nullptr, &destRect, angle, nullptr, SDL_FLIP_NONE);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 51, 0, 102, 255);
        SDL_RenderFillRect(renderer, &destRect);
    }
}

void GameRender::ProjectileRender(Projectile p, SDL_Renderer *renderer)
{
    SDL_Rect destRect = {
        static_cast<int>(p.cord.second * 100 + (100 - p.taille.first) / 2),
        static_cast<int>(p.cord.first * 100 + (100 - p.taille.second) / 2),
        static_cast<int>(p.taille.first),
        static_cast<int>(p.taille.second)};

    if (projectileTexture)
    {
        SDL_RenderCopy(renderer, projectileTexture, nullptr, &destRect);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 51, 0, 102, 255);
        SDL_RenderFillRect(renderer, &destRect);
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
     DrawThickRect(renderer, filledRect, 5);
}