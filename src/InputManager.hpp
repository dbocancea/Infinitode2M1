#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include<iostream>
#include <SDL.h>

class InputManager
{
    public:
        int nbk;
        const Uint8* keys;
        InputManager(const Uint8* keys , int nbk);
        void GestionClavier(bool* runing);
};

#endif