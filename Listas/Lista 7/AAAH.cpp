#include <iostream>
#include <vector>
using namespace std;

const int moves_row[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int moves_col[] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool Is_valid(vector<vector<int>> board, vector<vector<int>> visited, int row, int col, int rows)
{
    if ((row >= 0) && (row < rows) && (col >= 0) && (col < 10) && (board[row][col] == 0))
        return true;
    return false;
}

bool KnightTour(vector<vector<int>> &board, vector<vector<int>> &visited, int row, int col, int step, int max_moves, int rows)
{
    if (step == max_moves)
        return true;
    else
    {
        for (int i = 0; i < 8; i++)
        {
            int nextRow = row + moves_row[i];
            int nextCol = col + moves_col[i];

            if (Is_valid(board, visited, nextRow, nextCol, rows))
            {
                step++;
                board[nextRow][nextCol] = step;
                visited[nextRow][nextCol]++;
                if (KnightTour(board, visited, nextRow, nextCol, step, max_moves, rows))
                    return true;
                else
                {
                    step--;
                    max_moves--;
                    board[nextRow][nextCol] = 0;
                    visited[nextRow][nextCol]--;
                }
            }    
        }
    }

    return false;
}

int main()
{
    int cases = 1;   
    while (true)
    {
        int rows, size = 100;
        cin >> rows;
        if (rows == 0)
            break;
        
        vector<vector<int>> board(10, vector<int>(10, 0));

        for (int i = 0; i < rows; i++)
        {
            int skip, columns;
            cin >> skip >> columns;

            for (int j = 0; j < skip; j++)
            {
                board[i][j] = -1;
                size--;
            }
            for (int j = skip + columns; j < 10; j++)
            {
                board[i][j] = -1;
                size--;
            }
        }
        for (int i = rows; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                board[i][j] = -1;
                size--;
            }
        }
        
        pair<int, int> start = {-1, -1};
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (board[i][j] == 0)
                {
                    start = {i, j};
                    break;
                }
            }
            if (start.first != -1 && start.second != -1)
                break;
        }
        board[start.first][start.second] = 1;
        vector<vector<int>> visited = board;

        bool tour = KnightTour(board, visited, start.first, start.second, 1, size, rows);
        int squares = 0;
        
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                cout << visited[i][j] << " ";
                if (visited[i][j] == 0)
                    squares++;
            }
            cout << endl;
        }
        
        if (squares == 1)
            cout << "Case " << cases << ", " << squares << " square can not be reached.\n";
        else
            cout << "Case " << cases << ", " << squares << " squares can not be reached.\n";
        cases++;
    }
    
    return 0;
}