#include"Enemy.hpp"
Enemy::Enemy(){}
Enemy::Enemy(float h, float l, float hp, float speed, std::pair<float, float> start)
    : hp(hp), speed(speed)
{
    this->taille = {l, h}; // length (width), height
    this->cord = start;    // x, y position
}

void Enemy::Move(int dirx, int diry)
{
    if (dirx > 0)      this->cord.second += speed;
    else if (dirx < 0) this->cord.second -= speed;

    if (diry > 0)      this->cord.first += speed;
    else if (diry < 0) this->cord.first -= speed;
}