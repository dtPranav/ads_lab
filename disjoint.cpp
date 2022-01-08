#include <bits/stdc++.h>
using namespace std;

class DisjointUnionSets
{

    vector<int> rank, parent;
    int n;

public:
    DisjointUnionSets(int n)
    {
        rank.resize(n);
        parent.resize(n);
        this->n = n;
        makeSet();
    }

    void makeSet()
    {

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
        {

            return find(parent[x]);
        }

        return x;
    }

    void Union(int x, int y)
    {

        int xRoot = find(x);
        int yRoot = find(y);

        if (xRoot == yRoot)
            return;

        if (rank[xRoot] < rank[yRoot])
            parent[xRoot] = yRoot;

        else if (rank[yRoot] < rank[xRoot])
            parent[yRoot] = xRoot;

        else
        {

            parent[yRoot] = xRoot;

            rank[xRoot] = rank[xRoot] + 1;
        }
    }
};
vector<pair<int, int>> p = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
int countIslands(vector<vector<int>> a)
{
    // int n = a.size();
    // int m = a[0].size();

    // DisjointUnionSets *dus = new DisjointUnionSets(n * m);

    // for (int j = 0; j < n; j++)
    // {
    //     for (int k = 0; k < m; k++)
    //     {

    //         if (a[j][k] == 0)
    //             continue;
    //         for (int l = 0; l < 8; l++)
    //             if (j + p[l].first < n && j + p[l].first >= 0 && k + p[l].second < m && k + p[l].second >= 0 && a[j + p[l].first][k + p[l].second] == 1)
    //                 dus->Union((j * m) + k, ((j + p[l].first) * m) + k + p[l].second);
    //     }
    // }
    // set<int> s;
    // int numberOfIslands = 0;
    // for (int j = 0; j < n; j++)
    //     for (int k = 0; k < m; k++)
    //         if (a[j][k] == 1)
    //             s.insert(dus->find(j * m + k));
    // return s.size();
    int n = a.size();
    int m = a[0].size();
    DisjointUnionSets *ds = new DisjointUnionSets(n * m);
    // int c[n * m];
    // memset(c, -1, sizeof(c));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!a[i][j])
                continue;
            else
                for (int k = 0; k < 8; k++)
                    if (i + p[k].first < n && i + p[k].first >= 0 && j + p[k].second < m && j + p[k].second >= 0 && a[i + p[k].first][j + p[k].second] == 1)
                        ds->Union(i * m + j, (i + p[k].first) * m + (j + p[k].second));
        }
    }
    set<int> s;
    for (int j = 0; j < n; j++)
        for (int k = 0; k < m; k++)
            if (a[j][k])
                s.insert(ds->find(j * m + k));
    return s.size();
}
int main(void)
{
    vector<vector<int>> a = {{1, 1, 0, 0, 0},
                             {0, 1, 0, 0, 1},
                             {1, 0, 0, 1, 1},
                             {0, 0, 0, 0, 0},
                             {1, 0, 1, 0, 1}};
    cout << "Given input" << endl;
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Number of Islands is: "
         << countIslands(a) << endl;
}
