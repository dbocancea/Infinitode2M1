#ifndef GRID_HPP
#define GRID_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <vector>
#include <array>
using namespace std;
class Grid
{
public:
    vector<pair<float, float>> cord_chemain;
    char map[10][10];
    char chemain;
    char tour;
    char mur;
    char depart;
    char arrive;
    pair<int, int> start;
    pair<int, int> end;
    void CalculerChaiman();
    Grid(string file);
    bool loadFromFile(string load);
    vector<pair<pair<float, float>, bool>> towers;
};

#endif