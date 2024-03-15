#include<iostream>
using namespace std;
int n;
int check[10][10];

void traverse( int **m, int row, int col )
{
    //base cases 
    if(row >= n || col >= n || row < 0 || col < 0)
        return;
    if(check[row][col] == -1|| m[row][col] == 0)
        return;
        
    //marking visited boxes with -1;
    check[row][col] = -1;
    
    //recursive cases
    traverse( m,  row - 2,  col - 1 );
    traverse( m,  row - 2,  col + 1 );
    
    traverse( m,  row - 1,  col - 2 );
    traverse( m,  row - 1,  col + 2 );
    
    traverse( m,  row + 1,  col - 2 );
    traverse( m,  row + 1,  col + 2 );
    
    traverse( m,  row + 2,  col - 1 );
    traverse( m,  row + 2,  col + 1 );
   
    
}

int main()
{
   
    cin >> n;
    int **m = new int*[n];
    for(int i = 0; i < n; i++)
        m[i] = new int[n];
    
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> m[i][j];

    traverse(m, 0, 0);
    int count = 0;

    //checking out how many rows remain unvisited
    check[0][0] = -1;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
           if(check[i][j] != -1 && m[i][j] == 1)
                count++;
        }
    }
    cout << count << endl;
    
    return 0;
}