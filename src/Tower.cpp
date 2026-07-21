#include "Tower.hpp"

Tower::Tower(float range , float attack , float attack_speed , pair<float , float> cord , float h , float l )
     : range(range) , attack(attack) , attack_speed(attack_speed)
{
    this->taille = {l, h}; 
    this->cord = cord;   
};
void Find(vector <Enemy> enemys)
{
    Enemy target;
    float diff = 10;
    for( int i = 0; i<enemys.size() ; i++ )
    {
    }
}