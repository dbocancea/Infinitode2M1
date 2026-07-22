#include "InputManager.hpp"

InputManager::InputManager(const Uint8 *keys , int nbk)  : nbk(nbk)
{
    this->keys = keys;
}

void InputManager::GestionClavier(bool *runing)
{
    if (this->keys[SDL_SCANCODE_ESCAPE])
        *runing = true;
    if (keys[SDL_SCANCODE_LEFT])
        puts("LEFT");
    if (keys[SDL_SCANCODE_RIGHT])
        puts("RIGHT");
    if (keys[SDL_SCANCODE_UP])
        puts("UP");
    if (keys[SDL_SCANCODE_DOWN])
        puts("DOWN");
}