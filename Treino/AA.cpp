#include <iostream>
#include <vector>
using namespace std;

vector<int> moves_x = { -1, -2, -2, -1, +1, +2, +2, +2 };
vector<int> moves_y = { -2, -1, +1, +2, +2, +1, -1, -2 };
static int minCount = 0;

bool isValid(vector<vector<int>> board, int row, int col)
{
	if ((row >= 0) && (row < 10) && (col >= 0) && (col < 10) && board[row][col] == 1)
		return true;
	return false;
}

void funkyChessBoard(vector<vector<int>> board, int row, int col, int count)
{
	minCount = min(minCount, count);

	for (int i = 0; i < moves_x.size(); i++)
    {
		int nextRow = row + moves_x[i];
		int nextCol = col + moves_y[i];

		if (isValid(board, nextRow, nextCol))
        {
			board[nextRow][nextCol] = 2; // 2 = knight placed
			funkyChessBoard(board, nextRow, nextCol, count - 1);
			board[nextRow][nextCol] = 1; // 1 = knight removed
		}
	}
}

int main()
{
	int N;
    cin >> N;
    vector<vector<int>> board(N, vector<int>(N));

    int minCount = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int value;
            cin >> value;

            if (value == 1)
                minCount++;
            board[i][j] = value;
        }
    }

    funkyChessBoard(board, 0, 0, minCount);
    cout << minCount << endl;
}