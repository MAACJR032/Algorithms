#include <iostream>
#include <vector>
using namespace std;

const int moves_row[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int moves_col[] = {-1, 1, -2, 2, -2, 2, -1, 1};

bool Is_valid(vector<vector<int>> board, vector<vector<int>> visited, int row, int col)
{
    if ((row >= 0) && (row < 10) && (col >= 0) && (col < 10) && (board[row][col] == 0))
        return true;
    return false;
}

bool KnightTour(vector<vector<int>> &board, vector<vector<int>> &visited, int row, int col, int step, int max_moves, int &max_steps)
{
    if (step == max_moves)
    {

        return true;
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            int nextRow = row + moves_row[i];
            int nextCol = col + moves_col[i];

            if (Is_valid(board, visited, nextRow, nextCol))
            {
                step;
                board[nextRow][nextCol] = step+1;
                visited[nextRow][nextCol] = 1;
                if (KnightTour(board, visited, nextRow, nextCol, step+1, max_moves, max_steps))
                    return true;
                else
                {
                    max_moves--;
                    board[nextRow][nextCol] = 0;
                    // visited[nextRow][nextCol]--;
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
            {
                board[i][j] = 0;
            }

            size += columns;
        }
        
        board[0][0] = 1;
        int max_steps = 0;
        vector<vector<int>> visited = board;

        bool tour = KnightTour(board, visited, 0, 0, 1, size, max_steps);
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
