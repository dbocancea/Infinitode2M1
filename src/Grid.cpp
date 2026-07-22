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
            if (line[j] == this->tour)
                this->towers.push_back({{i, j}, 0});
            if (line[j] == this->depart)
                this->start = pair<int, int>{i, j};
            if (line[j] == this->arrive)
                this->end = pair<int, int>{i, j};
        }
        i++;
    }
    return true;
}

void Grid::CalculerChaiman()
{
    cord_chemain.clear();

    std::vector<std::vector<bool>> visited(10, std::vector<bool>(10, false));
    std::pair<int, int> current = this->start; // {i, j} = {ligne, colonne}

    while (current != this->end)
    {
        cord_chemain.push_back(current);
        visited[current.first][current.second] = true;

        // 4 directions : haut, bas, gauche, droite
        static const std::array<std::pair<int, int>, 4> dirs = {
            std::pair<int, int>{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        bool found = false;
        for (const auto &d : dirs)
        {
            int ni = current.first + d.first;
            int nj = current.second + d.second;

            if (ni < 0 || ni >= 10 || nj < 0 || nj >= 10)
                continue;

            char c = this->map[ni][nj];
            bool isWalkable = (c == chemain || c == arrive || c == depart);

            if (isWalkable && !visited[ni][nj])
            {
                current = {ni, nj};
                found = true;
                break;
            }
        }

        if (!found) // chemin cassé ou mal formé dans le fichier
        {
            std::cerr << "Chemin invalide : impossible de continuer depuis ("
                      << current.first << "," << current.second << ")\n";
            return;
        }
    }

    cord_chemain.push_back(this->end); //
}

