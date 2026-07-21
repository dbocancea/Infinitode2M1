#ifndef TOWER_HPP
#define TOWER_HPP

#include "Entity.hpp"
#include "Enemy.hpp"
class Tower : public Entity
{
public:
    float range;
    float attack;
    float attack_speed;

    Tower(float range , float attack , float attack_speed , pair<float , float> cord , float h , float l );
    void Find(vector <Enemy> enemys);
    void Attack();
};

#endif