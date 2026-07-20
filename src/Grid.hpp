#ifndef GRID_HPP
#define  GRID_HPP
#include<iostream>
#include<string>
#include <fstream>
using namespace std;
class Grid 
{
    public : 
        char map[10][10];
        char chemain;
        char tour;
        char mur;
        char depart;
        char arrive;
        pair<int ,int> start;
        pair<int ,int> end;

        Grid( string file );
        bool loadFromFile(string load);
        
};

#endif