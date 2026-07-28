namespace TopoSort
{
    int n;
    vector<vector<int>> adj(n + 1);

    // Kahn 算法：若存在环，返回空数组
    vector<int> sort()
    {
        vector<int> inDegree(n + 1, 0);
        for (int u = 1; u <= n; ++u)
        {
            for (int v : adj[u])
                inDegree[v]++;
        }

        queue<int> q;
        for (int i = 1; i <= n; ++i)
        {
            if (inDegree[i] == 0)
                q.push(i);
        }

        vector<int> order;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (int v : adj[u])
            {
                inDegree[v]--;
                if (inDegree[v] == 0)
                    q.push(v);
            }
        }

        if ((int)order.size() != n)
            return {};
        return order;
    }
}


