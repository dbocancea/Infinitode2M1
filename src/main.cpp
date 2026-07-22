#include <SDL.h>
#include <iostream>
#include <vector>
#include "Grid.hpp"
#include "GameRender.hpp"
#include "Enemy.hpp"
#include <unistd.h>
#include "InputManager.hpp"
#include "Projectile.hpp"
int main(int argc, char *argv[])
{
    Uint32 startTime = SDL_GetTicks();
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Erreur SDL_Init: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Infinitode - Test Rendu",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          1000, 1000, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "Erreur Fenêtre: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        std::cerr << "Erreur Renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Grid maGrille("../sprites/chem.txt");
    vector<Tower> tours;
    vector<Enemy> ennemis;
    vector<Projectile> projectiles;
    maGrille.CalculerChaiman();
    GameRender gameRender(maGrille, tours, ennemis);
    vector<Enemy> enemys;
    bool running = true;
    SDL_Event event;
    vector<int> parc = {0};
    int time;
    int second_time = -1;
    int nbk;
    const Uint8 *keys = SDL_GetKeyboardState(&nbk);
    InputManager input(keys, nbk, maGrille.start);
    while (running)
    {
        Uint32 elapsed = SDL_GetTicks() - startTime;
        time = elapsed / 1000;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }
        bool creer_tour = false;
        input.GestionClavier(&running, &creer_tour);
        if (creer_tour)
        {
            Tower t(5, 10, 2, input.player, 75, 75);
            tours.push_back(t);
        }
        for (int i = 0; i < enemys.size(); i++)
        {
            if (parc[i] < maGrille.cord_chemain.size())
            {
                auto target = maGrille.cord_chemain[parc[i]];

                float diffY = target.first - enemys[i].cord.first;   // Ligne
                float diffX = target.second - enemys[i].cord.second; // Colonne

                if (abs(diffX) < 0.05f && abs(diffY) < 0.05f)
                {
                    enemys[i].cord = target;
                    parc[i]++;
                }
                else
                {
                    int dirX = (diffX > 0) - (diffX < 0);
                    int dirY = (diffY > 0) - (diffY < 0);

                    enemys[i].Move(dirX, dirY);
                }
            }
            else
            {
                cout << "L'ennemi a atteint la fin !" << endl;
                running = false;
            }
        }
        if ((time % 2 == 0) && (time != second_time))
        {
            Enemy en(50, 50, 100, 0.05f, maGrille.start);
            enemys.push_back(en);
            parc.push_back(0);
        }
        for (auto &tw : tours)
        {
            int index = tw.Find(enemys);
            if (index != -1 && (time % 2 == 0) && (time != second_time))
            {
                Projectile p(tw.cord, enemys[index].cord, 0.05f, {20, 20}, index , tw);
                projectiles.push_back(p);
            }
        }

        for (int i = 0; i < projectiles.size(); i++)
        {
            bool touch = false;
            auto it = find(enemys.begin(), enemys.end(), enemys[projectiles[i].index]);
            if (it == enemys.end())
                projectiles.erase(projectiles.begin() + i);
            projectiles[i].Move(&touch);
            projectiles[i].UpdateCord(enemys[projectiles[i].index].cord);
            if (touch)
            {
                enemys[projectiles[i].index].hp -= projectiles[i].t.attack;
                projectiles.erase(projectiles.begin() + i);
            }
        }

        gameRender.GridRender(renderer);

        for (int k = 0; k < enemys.size(); k++)
        {
            if (enemys[k].hp <= 0)
                enemys.erase(enemys.begin() + k);
            gameRender.EntityRender(enemys[k], renderer);
        }

        for (auto &tw : tours)
            gameRender.TowerRender(tw, renderer);

        for (auto &proj : projectiles)
            gameRender.ProjectileRender(proj, renderer);
        gameRender.PlayerSelectRender(input, renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(32);
        if (time != second_time)
        {
            second_time = time;
            cout << "Time: " << time << endl;
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}