namespace LCA
{
    const int N = 200005;
    const int LOG = 20;

    int n;
    vector<int> depth;
    vector<vector<int>> up;
    vector<vector<int>> adj;

    void init(int nodeCount)
    {
        n = nodeCount;
        depth.assign(n + 1, 0);
        up.assign(LOG, vector<int>(n + 1, 0));
        adj.assign(n + 1, {});
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int p)
    {
        up[0][u] = p;
        for (int k = 1; k < LOG; k++)
        {
            up[k][u] = up[k - 1][up[k - 1][u]];
        }

        for (int v : adj[u])
        {
            if (v == p)
                continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    // root 通常传 1
    void build(int root = 1)
    {
        depth[root] = 0;
        dfs(root, 0);
    }

    int jump(int u, int step)
    {
        for (int k = 0; k < LOG; k++)
        {
            if (step & (1 << k))
                u = up[k][u];
        }
        return u;
    }

    int query(int u, int v)
    {
        if (depth[u] < depth[v])
            swap(u, v);

        u = jump(u, depth[u] - depth[v]);
        if (u == v)
            return u;

        for (int k = LOG - 1; k >= 0; k--)
        {
            if (up[k][u] != up[k][v])
            {
                u = up[k][u];
                v = up[k][v];
            }
        }
        return up[0][u];
    }

    int dist(int u, int v)
    {
        int p = query(u, v);
        return depth[u] + depth[v] - 2 * depth[p];
    }
}
