#include "Grid.hpp"

Grid::Grid(string file)
{

    this->chemain = '.';
    this->tour = 'T';
    this->mur = '#';
    this->depart = 'S';
    this->arrive = 'E';
    if (!loadFromFile(file))
    {
        cerr << "loadFormFile";
    }
}

bool Grid::loadFromFile(string file)
{
    ifstream file_o(file);

    if (!file_o)
        return false;

    string line;
    int i = 0;
    while (getline(file_o, line))
    {
        for (int j = 0; j < 10; j++)
        {
            this->map[i][j] = line[j];
            if (line[j] == this->depart)
                this->start = pair<int, int>{i, j};
            if (line[j] == this->arrive)
                this->end = pair<int, int>{i, j};
        }
        i++;
    }
    return true;
}