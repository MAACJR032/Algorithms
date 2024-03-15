#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool is_valid(int i, int j, vector<vector<int>> board, int rows)
{
    if (i >= 0 && i < rows && j >= 0 && j < board[i].size() && board[i][j] == -1)
        return true;
    return false;
}

bool knight_tour(vector<vector<int>> &board, int board_size, int rows, int i, int j, vector<pair<int, int>> moves)
{
    if (board_size == 0)
        return true;

    for(int k = 0; k < 8; k++)
    {
        int next_i = i + moves[k].first;
        int next_j = j + moves[k].second;

        if(is_valid(next_i, next_j, board, rows))
        {
            board[next_i][next_j] = 0;
            if (knight_tour(board, board_size-1, rows, next_i, next_j, moves))
                return true;
            board[i + moves[k].first][j + moves[k].second] = -1; // backtracking
        }
    }

  return false;
}

void start_knight_tour(vector<vector<int>> &board, int rows, int board_size, int cases, int steps)
{
    vector<pair<int, int>> moves = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    pair<int, int> start = {-1, -1};
    int j = 0;
    for (int i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (board[i][j] == -1)
            {
                start = {i, j};
                break;
            }
        }
        if (i != -1 && j != -1)
            break;
    }
    board[start.first][start.second] = 0;
    
    if (!knight_tour(board, board_size, rows, start.first, start.second, moves, steps))
        cout << "Case " << cases << ", 0 squares can not be reached.\n";
    else
    {
        int squares = 0;
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (board[i][j] == -1)
                    squares++;
        
        if (squares == 1)
            cout << "Case " << cases << ", " << squares << " square can not be reached.\n";
        else
            cout << "Case " << cases << ", " << squares << " squares can not be reached.\n";
    }
}

int main()
{
    int rows, cases = 1, size = 100;

    vector<vector<int>> board(10, vector<int>(10, -1));
    
    while (true)
    {
        cin >> rows;
        if (rows == 0)
            break;
        
        for (int i = 0; i < rows; i++)
        {
            int skip, columns;
            cin >> skip >> columns;

            for (int j = 0; j < skip; j++)
            {
                board[i][j] = -2;
                size--;
            }
            for (int j = skip + columns; j < 10; j++)
            {
                board[i][j] = -2;
                size--;
            }
        }
        for (int i = rows; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                board[i][j] = -2;
                size--;
            }
        }

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
        cout << endl; 
        
        start_knight_tour(board, rows, size, cases, 0);
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
        cout << endl;
        cases++;
    }

    return 0;
}