#include <iostream>
#include <vector>
using namespace std;

bool valid(vector<vector<int>> board, int row, int col)
{
    int i, j; 
    for (i = 0; i < col; i++) 
        if (board[i][row]) 
            return false; 

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
        if (board[j][i]) 
            return false; 
    for (i = row, j = col; j >= 0 && i < board.size(); i++, j--) 
        if (board[j][i]) 
            return false; 
  
    return true;
}
bool qns(int col, vector<vector<int>> &board)
{
    if (col == board.size())
        return true;
    else
    {
        for (int i = 0; i < board.size(); i++)
        {
            if (valid(board, i, col))
            {
                board[col][i] = 1;

                if (qns(col+1, board))
                    return true;
                else board[col][i] = 0;
            }
        }
        return false;
    }
}

int main()
{
    int n = 0;
    cin >> n;

    vector<vector<int>> board;
    board.resize(n);
    for (int i = 0; i < n; i++)
        board[i].resize(n, 0);

    if (qns(0, board))
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << board[i][j] << " ";
            cout << '\n';
        }
    }
    else cout << "Impossible\n";
    
    return 0;
}
