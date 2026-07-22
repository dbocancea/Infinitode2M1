#include "Projectile.hpp"

Projectile::Projectile(pair<float, float> cord, pair<float, float> target, float speed, pair<float, float> taille, int index) : speed(speed), index(index)
{
    this->cord = cord;
    this->target = target;
    this->taille = taille;
}

void Projectile::UpdateCord(pair<float, float> nCord)
{
    this->target = nCord;
}

void Projectile::Move(bool *touch)
{
    float diffY = target.first - cord.first;
    float diffX = target.second - cord.second;

    int dirY = (diffY > 0) - (diffY < 0);
    int dirX = (diffX > 0) - (diffX < 0);

    cord.first += dirY * speed;
    cord.second += dirX * speed;

    if (abs(diffX) < 0.05f && abs(diffY) < 0.05f)
        *touch = true;
}
