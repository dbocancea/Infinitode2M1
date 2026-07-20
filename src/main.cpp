#include <SDL.h>
#include <iostream>

SDL_Window* pWindow = nullptr;
SDL_Surface* win_surf = nullptr;
SDL_Surface* plancheSprites = nullptr;


int main ()
{   
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
		std::cerr <<"Echec de l'initialisation de la SDL "<<SDL_GetError() << std::endl;
		return 1;
    }

    pWindow = SDL_CreateWindow("Infinitode", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 680, 680, SDL_WINDOW_SHOWN);
    if (!pWindow) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    win_surf = SDL_GetWindowSurface(pWindow);
    
	plancheSprites = SDL_LoadBMP("../sprites/binfinitode_map_sprite.bmp");
    if (!plancheSprites) {
        std::cerr << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    SDL_Rect src_bg = { 0, 0, plancheSprites->w, plancheSprites->h };
    SDL_Rect bg     = { 0, 0, 680, 680 };
    
    SDL_SetColorKey(plancheSprites, false, 0);
    SDL_BlitScaled(plancheSprites, &src_bg, win_surf, &bg);
    SDL_UpdateWindowSurface(pWindow);

    bool running = true;
    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }
    }

    SDL_FreeSurface(plancheSprites);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}