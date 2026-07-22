#ifndef Enemy_HPP
#define Enemy_HPP

#include "Entity.hpp"

class Enemy : public Entity
{
    public:
        float hp;
        float speed;
        int id;
        static int next_id;
        Enemy(float h , float l , float hp , float speed , pair<float , float> start );
        void Move(int dirx , int diry);
        bool operator==(const Enemy& other) const {
        // Compare unique ID if you have one, or coordinates/properties:
        return this->cord == other.cord && this->hp == other.hp;
    }
    };

#endif