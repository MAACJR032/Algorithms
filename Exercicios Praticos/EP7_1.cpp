#include <iostream>
#include <vector>
using namespace std;

void find_subsets(int &sum, int d, int &num_subsets, vector<int> &numbers, int index)
{
    if (sum == d)
    {
        num_subsets++;
        return;
    }
    else if (sum > d)
    {
        if (index < numbers.size())
        {
            if (sum - numbers[index] < d)
                return;
        }
        
        for (int j = index; j < numbers.size(); j++)
        {
            sum -= numbers[j];
            find_subsets(sum, d, num_subsets, numbers, index+1);
            sum += numbers[j];
        }
    }

    return;   
}

int main()
{
    int cases, d;
    cin >> cases;

    for (int i = 0; i < cases; i++)
    {
        int n, sum = 0;
        cin >> n;

        vector<int> numbers;
        for (int j = 0; j < n; j++)
        {
            int num;
            cin >> num;

            numbers.push_back(num);
            sum += num;
        }
        
        cin >> d;
        int subsets = 0;
        find_subsets(sum, d, subsets, numbers, 0);
        
        cout << subsets << '\n';
    }
    
    return 0;
}
