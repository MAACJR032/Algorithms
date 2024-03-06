#include <iostream>
#include <vector>
using namespace std;

bool valid(vector<vector<int>> m, int l, int i)
{
    
}
bool qns(int l, vector<vector<int>> m)
{
    if (l == m.size())
        return true;
    else
    {
        for (int i = 0; i < m.size(); i++)
        {
            if (valid(m, l, i))
            {
                m[l][i] = 1;

                if (qns(l+1, m))
                    return true;
                else m[l][i] = 0;
            }
        }
        return false;
    }
}

int main()
{
    int n = 0;
    cin >> n;

    vector<vector<int>> a;
    a.resize(n);
    for (int i = 0; i < 10; i++)
        a[i].resize(n);

    return 0;
}