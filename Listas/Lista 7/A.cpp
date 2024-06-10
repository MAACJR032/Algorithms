#include <iostream>
#include <vector>
#define Visited 1
#define Unvisited 0
using namespace std;

const int moves_row[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int moves_col[] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool Is_valid(vector<vector<int>> board, int row, int col)
{
    if ((row >= 0) && (row < 10) && (col >= 0) && (col < 10) && (board[row][col] == 0))
        return true;
    return false;
}

bool KnightTour(vector<vector<int>> &board, int row, int col, int step, int max_moves, int &max_steps)
{
    if (step == max_moves)
    {
        max_steps = max(step, max_steps);
        return true;
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            int nextRow = row + moves_row[i];
            int nextCol = col + moves_col[i];

            if (Is_valid(board, nextRow, nextCol))
            {
                board[nextRow][nextCol] = Visited;
                max_steps = max(step + 1, max_steps);

                if (KnightTour(board, nextRow, nextCol, step + 1, max_moves, max_steps))
                    return true;
                else
                    board[nextRow][nextCol] = 0;
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
        int rows, size = 0;
        cin >> rows;
        if (rows == 0)
            break;
        
        vector<vector<int>> board(10, vector<int>(10, -1));
        for (int i = 0; i < rows; i++)
        {
            int skip, columns;
            cin >> skip >> columns;

            for (int j = skip; j < skip + columns; j++)
                board[i][j] = Unvisited;
            
            size += columns;
        }

        board[0][0] = 1;
        int max_steps = 0;

        bool tour = KnightTour(board, 0, 0, 1, size, max_steps);

        int squares = size - max_steps;
        if (squares == 1)
            cout << "Case " << cases << ", " << squares << " square can not be reached.\n";
        else
            cout << "Case " << cases << ", " << squares << " squares can not be reached.\n";
        
        cases++;
    }
    
    return 0;
}
