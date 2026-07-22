#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "Entity.hpp"
#include "Tower.hpp"
class Projectile : public Entity
{
    public:
        float speed;
        pair<float , float> target;
        int index;
        Tower t;
        Projectile(pair<float , float> cord , pair<float , float> target , float speed , pair<float , float> taille , int index , Tower t );
        void UpdateCord(pair<float , float> nCord);
        void Move(bool* touch);
};

#endif