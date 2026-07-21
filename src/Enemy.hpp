#ifndef Enemy_HPP
#define Enemy_HPP

#include "Entity.hpp"

class Enemy : public Entity
{
    public:
        float hp;
        float speed;
        Enemy(float h , float l , float hp , float speed , pair<float , float> start);
        void Move(int dirx , int diry);
};

#endif