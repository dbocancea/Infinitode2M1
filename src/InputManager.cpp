#include "InputManager.hpp"

InputManager::InputManager(const Uint8 *keys, int nbk, pair<float, float> player) : nbk(nbk)
{
    this->keys = keys;
    this->player = player;
}

void InputManager::GestionClavier(bool *runing, bool *creer_tour)
{

    static bool leftHeld = false, rightHeld = false, upHeld = false, downHeld = false;
    static Uint32 leftPressTime = 0, rightPressTime = 0, upPressTime = 0, downPressTime = 0;
    static Uint32 leftLastMove = 0, rightLastMove = 0, upLastMove = 0, downLastMove = 0;

    Uint32 now = SDL_GetTicks();
    const Uint32 REPEAT_DELAY = 500; // temps avant que ça commence a repeter
    const Uint32 REPEAT_RATE = 150;   // vitesse de repetition une fois lance

    if (this->keys[SDL_SCANCODE_ESCAPE])
        *runing = false;
    if (keys[SDL_SCANCODE_LEFT])
    {
        if (!leftHeld)
        {
            puts("LEFT");
            if (this->player.second > 0)
                this->player.second--;
            leftHeld = true;
            leftPressTime = now;
            leftLastMove = now;
        }
        else if (now - leftPressTime > REPEAT_DELAY && now - leftLastMove > REPEAT_RATE)
        {
            puts("LEFT");
            if (this->player.second > 0)
                this->player.second--;
            leftLastMove = now;
        }
    }
    else
        leftHeld = false;

    if (keys[SDL_SCANCODE_RIGHT])
    {
        if (!rightHeld)
        {
            puts("RIGHT");
            if (this->player.second < 9)
                this->player.second++;
            rightHeld = true;
            rightPressTime = now;
            rightLastMove = now;
        }
        else if (now - rightPressTime > REPEAT_DELAY && now - rightLastMove > REPEAT_RATE)
        {
            puts("RIGHT");
            if (this->player.second < 9)
                this->player.second++;
            rightLastMove = now;
        }
    }
    else
        rightHeld = false;

    if (keys[SDL_SCANCODE_UP])
    {
        if (!upHeld)
        {
            puts("UP");
            if (this->player.first > 0)
                this->player.first--;
            upHeld = true;
            upPressTime = now;
            upLastMove = now;
        }
        else if (now - upPressTime > REPEAT_DELAY && now - upLastMove > REPEAT_RATE)
        {
            puts("UP");
            if (this->player.first > 0)
                this->player.first--;
            upLastMove = now;
        }
    }
    else
        upHeld = false;

    if (keys[SDL_SCANCODE_DOWN])
    {
        if (!downHeld)
        {
            puts("DOWN");
            if (this->player.first < 9)
                this->player.first++;
            downHeld = true;
            downPressTime = now;
            downLastMove = now;
        }
        else if (now - downPressTime > REPEAT_DELAY && now - downLastMove > REPEAT_RATE)
        {
            puts("DOWN");
            if (this->player.first < 9)
                this->player.first++;
            downLastMove = now;
        }
    }
    else
        downHeld = false;

    if (keys[SDL_SCANCODE_SPACE])
    {
        puts("SPACE");
        *creer_tour = true;
    }
}