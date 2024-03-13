#include <iostream>
#include <vector>
using namespace std;

bool isValid(int x, int y, vector<vector<int>> &board, int rows) 
{ 
    if (x >= 0 && x < 10 && y >= 0 && y < rows && board[x][y] == -1)
        return true;
    return false; 
} 

int solveKTUtil(int x, int y, int movei, vector<vector<int>> board, int xMove[8], int yMove[8], int rows) 
{ 
    int k, next_x, next_y; 
    if (movei == 10 * rows) 
        return 1; 
  
    /* Try all next moves from 
    the current coordinate x, y */
    for (k = 0; k < rows; k++)
    { 
        next_x = x + xMove[k]; 
        next_y = y + yMove[k]; 

        if (isValid(next_x, next_y, board, rows))
        { 
            board[next_x][next_y] = movei; 
            if (solveKTUtil(next_x, next_y, movei + 1, board, xMove, yMove, rows) == 1) 
                return 1; 
            else // backtracking 
                board[next_x][next_y] = -1; 
        } 
    } 
    return 0; 
} 

int solveKT(vector<vector<int>> &board, int rows, int start) 
{ 
    /* xMove[] and yMove[] define next move of Knight. 
    xMove[] is for next value of x coordinate 
    yMove[] is for next value of y coordinate */
    int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 }; 
    int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 }; 
  
    /* Start from 0,start and explore all tours using 
    solveKTUtil() */

    if (solveKTUtil(0, start, 1, board, xMove, yMove, rows) == 0)
    { 
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < rows; j++)
                if (board[i][j] == 0)
                {
                    
                }
                
            
        }
        
    } 
    else
         cout << "Case , 0 squares can not be reached.\n";
  
    return 1; 
} 

int main()
{
    int rows, cases = 1, start = 0;
    cin >> rows;

    vector<vector<int>> board(rows);
    for (int i = 0; i < rows; i++)
        board[i].resize(10, -1);
    
    while (rows > 0)
    {
        int squares = 0;
        for (int i = 0; i < rows; i++)
        {
            int skip, columns;
            cin >> skip >> columns;

            if (i == 0)
                start = skip;
            
            for (int j = 0; j < skip; j++)
                board[i][j] = 0;
            for (int j = skip + columns; j < 10; j++)
                board[i][j] = 0;
        }
        // for (int i = 0; i < 10; i++)
        // {
        //     for (int j = 0; j < rows; j++)
        //         cout << board[i][j] << " ";
        //     cout << endl;
        // }
        
        //solveKT(board, rows, start);
        // squares = FindSquares();

        // if (squares == 1)
        //     cout << "Case " << cases << ", " << squares << " square can not be reached.\n";
        // else
            // cout << "Case " << cases << ", " << squares << " squares can not be reached.\n";
        
        cin >> rows;
    }
    

    
    return 0;
}
