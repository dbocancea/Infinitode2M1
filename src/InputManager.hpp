#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include<iostream>
#include <SDL.h>
#include<array>
#include <utility>
#include <vector>

using namespace std;
class InputManager
{
    public:
        int nbk;
        const Uint8* keys;
        pair<float , float> player;
        const float playerSize = 100.0f;
        InputManager(const Uint8* keys , int nbk , pair<float , float> player);
        void GestionClavier(bool* runing , bool *crrer_tour);
};

#endif