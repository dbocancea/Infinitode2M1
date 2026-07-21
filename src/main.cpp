// #include <SDL.h>
// #include <iostream>

// SDL_Window* pWindow = nullptr;
// SDL_Surface* win_surf = nullptr;
// SDL_Surface* plancheSprites = nullptr;


// int main ()
// {   
//     if (SDL_Init(SDL_INIT_VIDEO) != 0 )
//     {
// 		std::cerr <<"Echec de l'initialisation de la SDL "<<SDL_GetError() << std::endl;
// 		return 1;
//     }

//     pWindow = SDL_CreateWindow("Infinitode", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 680, 680, SDL_WINDOW_SHOWN);
//     if (!pWindow) {
//         std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
//         return 1;
//     }
    
//     win_surf = SDL_GetWindowSurface(pWindow);
    
// 	plancheSprites = SDL_LoadBMP("../sprites/binfinitode_map_sprite.bmp");
//     if (!plancheSprites) {
//         std::cerr << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
//         return 1;
//     }
    
//     SDL_Rect src_bg = { 0, 0, plancheSprites->w, plancheSprites->h };
//     SDL_Rect bg     = { 0, 0, 680, 680 };
    
//     SDL_SetColorKey(plancheSprites, false, 0);
//     SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);
//     SDL_UpdateWindowSurface(pWindow);

//     bool running = true;
//     SDL_Event e;
//     while (running) {
//         while (SDL_PollEvent(&e)) {
//             if (e.type == SDL_QUIT) running = false;
//         }
//     }

//     SDL_FreeSurface(plancheSprites);
//     SDL_DestroyWindow(pWindow);
//     SDL_Quit();
//     return 0;
// }

#include <SDL.h>
#include <iostream>
#include <vector>
#include "Grid.hpp"
#include "GameRender.hpp"
#include "Enemy.hpp" 
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur SDL_Init: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Infinitode - Test Rendu", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          1000, 1000, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Erreur Fenêtre: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Erreur Renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    Grid maGrille("../sprites/chem.txt");
    std::vector<Entity> tours;   
    std::vector<Entity> ennemis;
    maGrille.CalculerChaiman(); 
    for (int i = 0; i< maGrille.cord_chemain.size() ; i++ )
        cout << "( " << maGrille.cord_chemain[i].first << " , " << maGrille.cord_chemain[i].second << " )" << endl;
    GameRender gameRender(maGrille, tours, ennemis);

    Enemy e( 50 , 50 , 100 , 0.05f , maGrille.start);
    bool running = true;
    SDL_Event event;
    int parc = 0;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
            
        }

        if (parc < maGrille.cord_chemain.size())
        {
            auto target = maGrille.cord_chemain[parc];

            float diffY = target.first  - e.cord.first;  // Ligne
            float diffX = target.second - e.cord.second; // Colonne

            if (abs(diffX) < 0.05f && abs(diffY) < 0.05f)
            {
                e.cord = target; 
                parc++;          
            }
            else
            {
                int dirX = (diffX > 0) - (diffX < 0);
                int dirY = (diffY > 0) - (diffY < 0);
                
                e.Move(dirX, dirY);
            }
        }
        else
        {
            std::cout << "L'ennemi a atteint la fin !" << std::endl;
            running = false; 
        }

        gameRender.GridRender(renderer);
        gameRender.EntityRender(e, renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}