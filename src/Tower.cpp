#include "Tower.hpp"

Tower::Tower(float range, float attack, float attack_speed, pair<float, float> cord, float h, float l)
    : range(range), attack(attack), attack_speed(attack_speed)
{
    this->taille = {l, h};
    this->cord = cord;
};
int Tower::Find(const vector<Enemy>& enemies)
{
    if (enemies.empty())
        return -1;

    auto distSq = [this](const Enemy& e) {
        float dx = e.cord.second - this->cord.second;
        float dy = e.cord.first  - this->cord.first;
        return dx * dx + dy * dy;
    };

    auto it = std::min_element(enemies.begin(), enemies.end(),
        [&](const Enemy& a, const Enemy& b) {
            return distSq(a) < distSq(b);
        });

    if (distSq(*it) <= range * range)
        return static_cast<int>(distance(enemies.begin(), it));
    
        
    return -1; 
}
