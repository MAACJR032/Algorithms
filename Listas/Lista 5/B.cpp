#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Graph
{
    private:
        unordered_map<string, vector<string>> teams;
        set<string> students;
        map<string, int> ranking;
        map<int, vector<string>> ranked;
        set<string> undef;
        int numVertices;
    public:
        Graph(int n)
        {
            numVertices = n;
        }

        void setEdge(string name1, string name2)
        {
            teams[name1].push_back(name2);
            teams[name2].push_back(name1);
        }

        void setStudent(string name)
        {
            students.insert(name);
        }

        void BFS(queue<string> &q)
        {
            q.push("Ahmad");
            ranking["Ahmad"] = 0;

            while (!q.empty())
            {
                string curr = q.front();
                q.pop();

                for (auto team : teams[curr])
                {
                    if (!ranking.count(team))
                    {
                        ranking[team] = ranking[curr] + 1;
                        q.push(team);
                    }
                }
            }
        }

        void Order()
        {
            for (auto student : students)
            {
                if (ranking.count(student))
                    ranked[ranking[student]].push_back(student);
                else
                    undef.insert(student);
            }
        }
        
        void printRank()
        {
            cout << students.size() << '\n';

            for (auto all : ranked)
                for (auto student : all.second)
                    cout << student << " " << all.first << '\n';

            for (auto it = undef.begin(); it != undef.end(); it++)
                cout << *it << " undefined" << '\n';
        }
};

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;

        Graph g(n);

        for (int i = 0; i < n; i++)
        {
            string names[3];
            cin >> names[0] >> names[1] >> names[2];

            for (int j = 0; j < 3; j++)
            {
                for (int k = j + 1; k < 3; k++)
                    g.setEdge(names[j], names[k]);
                g.setStudent(names[j]);
            }
        }

        queue<string> q;
        g.BFS(q);
        g.Order();
        g.printRank();
    }

    return 0;
}