#include <iostream>
#include <vector>
#define Visisted 1
#define Unvisited 0
using namespace std;

const vector<int> moves_row = {1, -1, 0, 0};
const vector<int> moves_col = {0, 0, -1, 1};

bool is_Valid(int x, int y, int rows, int width, vector<vector<int>> path, string *maze)
{
    if ((x >= 0) && (x < rows) && (y >= 0) && (y < width) && (path[x][y] == Unvisited))
    {
        if (maze[x][y] == '#')
            return false;
        return true;
    }
    return false;
}

bool findTreasure(string *maze, vector<vector<int>> &path, int x, int y, int rows, int width, int &spikes, int max_avoid)
{
    if (spikes * 2 > max_avoid)
        return false;
    
    for (int i = 0; i < 4; i++)
    {
        int next_row = x + moves_row[i];
        int next_col = y + moves_col[i];

        if (is_Valid(next_row, next_col, rows, width, path, maze))
        {
            if (maze[next_row][next_col] == 'x')
                return true;
            else if (maze[next_row][next_col] == 's')
                spikes++;

            path[next_row][next_col] = 1;
            if (findTreasure(maze, path, next_row, next_col, rows, width, spikes, max_avoid))
                return true;
            
            if (maze[next_row][next_col] == 's')
                spikes--;
            path[next_row][next_col] = 0;
        }
    }
    
    return false;
}

int main()
{
    int rows, width, max_avoid;
    cin >> rows >> width >> max_avoid;
    
    string maze[rows];

    pair<int, int> start_pos;
    for (int i = 0; i < rows; i++)
    {
        cin >> maze[i];

        for (int j = 0; j < width; j++)
        {
            if (maze[i][j] == '@')
            {
                start_pos.first = i;
                start_pos.second = j;
            }      
        }
    }

    int spikes = 0;
    vector<vector<int>> path(rows, vector<int>(width, Unvisited));
    path[start_pos.first][start_pos.second] = Visisted;

    bool found = findTreasure(maze, path, start_pos.first, start_pos.second, rows, width, spikes, max_avoid);
    if (found)
        cout << "SUCCESS\n";
    else
        cout << "IMPOSSIBLE\n";
    
    return 0;
}
