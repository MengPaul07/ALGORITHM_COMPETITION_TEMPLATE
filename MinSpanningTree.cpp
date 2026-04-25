namespace MinSpanningTree
{
    struct Kruskal
    {
        struct Edge
        {
            int u, v, w;
        };

        int n;
        vector<Edge> edges;
        vector<int> parent, sz;

        explicit Kruskal(int n) : n(n), parent(n), sz(n, 1)
        {
            iota(parent.begin(), parent.end(), 0);
        }

        int find(int x)
        {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        }

        bool unite(int x, int y)
        {
            x = find(x);
            y = find(y);
            if (x == y)
                return false;
            if (sz[x] < sz[y])
                swap(x, y);
            parent[y] = x;
            sz[x] += sz[y];
            return true;
        }

        void addEdge(int u, int v, int w)
        {
            edges.push_back({u, v, w});
        }

        // 返回最小生成树权值；若图不连通返回 -1
        int build()
        {
            sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b)
                 { return a.w < b.w; });
            int mstWeight = 0;
            int used = 0;
            for (const auto &e : edges)
            {
                if (unite(e.u, e.v))
                {
                    mstWeight += e.w;
                    used++;
                }
            }
            return used == n - 1 ? mstWeight : -1;
        }
    };

    struct Prim
    {
        int n;
        vector<vector<pair<int, int>>> adj;

        explicit Prim(int n) : n(n), adj(n) {}

        void addEdge(int u, int v, int w)
        {
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // 返回最小生成树权值；若图不连通返回 -1
        int build(int start = 0)
        {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
            vector<bool> inMst(n, false);
            pq.push({0, start});

            int mstWeight = 0;
            int used = 0;
            while (!pq.empty())
            {
                auto [w, u] = pq.top();
                pq.pop();
                if (inMst[u])
                    continue;
                inMst[u] = true;
                mstWeight += w;
                used++;

                for (const auto &[v, nw] : adj[u])
                {
                    if (!inMst[v])
                        pq.push({nw, v});
                }
            }
            return used == n ? mstWeight : -1;
        }
    };
}