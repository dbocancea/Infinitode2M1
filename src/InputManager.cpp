#include "InputManager.hpp"

InputManager::InputManager(const Uint8 *keys, int nbk, pair<float, float> player) : nbk(nbk)
{
    this->keys = keys;
    this->player = player;
}

void InputManager::GestionClavier(bool *runing , bool *creer_tour)
{
    if (this->keys[SDL_SCANCODE_ESCAPE])
        *runing = false;
    if (keys[SDL_SCANCODE_LEFT])
    {
        puts("LEFT");
        if (this->player.second > 0)
            this->player.second--;
    }

    if (keys[SDL_SCANCODE_RIGHT])
    {
        puts("RIGHT");
        if (this->player.second < 9)
            this->player.second++;
    }
    if (keys[SDL_SCANCODE_UP])
    {
        puts("UP");
        if (this->player.first > 0)
            this->player.first--;
    }
    if (keys[SDL_SCANCODE_DOWN])
    {
        puts("DOWN");
        if (this->player.first < 9)
            this->player.first++;
    }
    if (keys[SDL_SCANCODE_SPACE])
    {
        puts("SPACE");
        *creer_tour= true;
    }
}