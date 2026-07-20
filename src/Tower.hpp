#ifndef TOWER_HPP
#define TOWER_HPP

#include "Entity.hpp"
class Tower : Entity
{
    public :
    float range;
    float attack;
    float attack_speed;
    
    void Find();
    void Attack();
};

#endif