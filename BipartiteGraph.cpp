#include <bits/stdc++.h>
using namespace std;

namespace BipartiteColoring
{
    const int SIZE = 100000 + 10;
    vector<int> edge[SIZE];
    int color[SIZE]; // -1: uncolored, 0/1: two parts

    void init(int n)
    {
        for (int i = 1; i <= n; i++)
            edge[i].clear();
        memset(color, -1, sizeof(color));
    }

    void addEdge(int u, int v)
    {
        edge[u].push_back(v);
        edge[v].push_back(u);
    }

    bool dfs(int u, int c)
    {
        color[u] = c;
        for (auto v : edge[u])
        {
            if (color[v] == -1)
            {
                if (!dfs(v, c ^ 1))
                    return false;
            }
            else if (color[v] == c)
            {
                return false;
            }
        }
        return true;
    }

    bool check(int n)
    {
        for (int i = 1; i <= n; i++)
        {
            if (color[i] == -1)
            {
                if (!dfs(i, 0))
                    return false;
            }
        }
        return true;
    }
}

namespace Hungarian
{
    const int SIZE = 1010;
    int n1, n2;
    vector<int> edge[SIZE]; // edge from left part [1..n1] to right part [1..n2]
    int match[SIZE];        // match[v]: right node v matched with left node
    bool vis[SIZE];

    void init(int leftSize, int rightSize)
    {
        n1 = leftSize;
        n2 = rightSize;
        for (int i = 1; i <= n1; i++)
            edge[i].clear();
        memset(match, 0, sizeof(match));
    }

    void addEdge(int u, int v)
    {
        edge[u].push_back(v);
    }

    bool find(int u)
    {
        for (auto v : edge[u])
        {
            if (vis[v])
                continue;
            vis[v] = true;
            if (match[v] == 0 || find(match[v]))
            {
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    int maxMatch()
    {
        int cnt = 0;
        for (int i = 1; i <= n1; i++)
        {
            memset(vis, false, sizeof(vis));
            if (find(i))
                cnt++;
        }
        return cnt;
    }
}
