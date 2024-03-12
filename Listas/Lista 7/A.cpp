#include <iostream>
#include <vector>
using namespace std;

int FindSquares()
{
    for (int i = 0; i < ; i++)
    {
        /* code */
    }
    
}

int main()
{
    int rows, cases = 1;
    cin >> rows;

    vector<vector<int>> board(rows);
    for (int i = 0; i < rows; i++)
        board[i].resize(10, 1);
    
    while (rows > 0)
    {
        int squares = 0;
        for (int i = 0; i < rows; i++)
        {
            int skip, columns;
            cin >> skip >> columns;
            for (int j = 0; j < skip; j++)
                board[i][j] = 0;
            for (int j = skip + columns; j < 10; j++)
                board[i][j] = 0;
        }
        
        squares = FindSquares();

        if (squares == 1)
            cout << "Case " << cases << ", " << squares << " square can not be reached.\n";
        else
            cout << "Case " << cases << ", " << squares << " squares can not be reached.\n";
        
        cin >> rows;
    }
    
 
    // vector<vector<pair<int, bool>>> board(rows);
    // for (int i = 0; i < rows; i++)
    // {
    //     int skip, columns;
    //     cin >> skip >> columns;
        
    //     board[i].resize(skip+columns, {0, true});
    //     for (int j = 0; j < skip; j++)
    //         board[i][j] = {0, false};
        
    // }
    
    return 0;
}