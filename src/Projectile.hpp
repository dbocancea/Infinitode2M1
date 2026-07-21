#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP
#include "Entity.hpp"

class Projectile : public Entity
{
    public:
        float speed;
        pair<float , float> target;
        int index;
        Projectile(pair<float , float> cord , pair<float , float> target , float speed , pair<float , float> taille , int index );
        void UpdateCord(pair<float , float> nCord);
        void Move();
};

#endif