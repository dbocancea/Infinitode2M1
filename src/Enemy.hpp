#ifndef Enemy_HPP
#define Enemy_HPP

#include "Entity.hpp"

class Enemy : Entity
{
    float hp;
    float speed;

    void Move();
};

#endif