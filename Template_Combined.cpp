#include <bits/stdc++.h>
using namespace std;

// =================================================================
// Math
// =================================================================
namespace Math
{
    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }

    int lcm(int a, int b)
    {
        return a / gcd(a, b) * b;
    }

    // 快速幂 a^b % mod
    long long power(long long base, long long exp, long long mod)
    {
        long long res = 1;
        base %= mod;
        while (exp > 0)
        {
            if (exp % 2 == 1)
                res = (res * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return res;
    }

    // 快速幂 a^b
    long long power(long long base, long long exp)
    {
        long long res = 1;
        while (exp > 0)
        {
            if (exp % 2 == 1)
                res *= base;
            base *= base;
            exp /= 2;
        }
        return res;
    }

    // 埃氏筛
    namespace Eratosthenes
    {
        const int N = 1000001;
        bool is_prime[N];

        void sieve(int n)
        {
            memset(is_prime, true, sizeof(is_prime));
            is_prime[0] = is_prime[1] = false;
            for (int p = 2; p * p <= n; p++)
            {
                if (is_prime[p])
                {
                    for (int i = p * p; i <= n; i += p)
                        is_prime[i] = false;
                }
            }
        }
    }

    // 欧拉筛 (线性筛)
    namespace Euler
    {
        const int N = 1000001;
        int primes[N];
        bool is_prime[N];
        int prime_count = 0;

        void sieve(int n)
        {
            memset(is_prime, true, sizeof(is_prime));
            is_prime[0] = is_prime[1] = false;
            for (int i = 2; i <= n; i++)
            {
                if (is_prime[i])
                {
                    primes[prime_count++] = i;
                }
                for (int j = 0; j < prime_count && i * primes[j] <= n; j++)
                {
                    is_prime[i * primes[j]] = false;
                    if (i % primes[j] == 0)
                    {
                        break;
                    }
                }
            }
        }
    }

    // 欧拉筛 (线性筛) + 欧拉函数
    namespace EulerPhi
    {
        const int N = 1000001;
        int primes[N];
        bool is_prime[N];
        int phi[N]; // phi[i] 存储 i 的欧拉函数值
        int prime_count = 0;

        void sieve(int n)
        {
            memset(is_prime, true, sizeof(is_prime));
            is_prime[0] = is_prime[1] = false;
            phi[1] = 1;
            for (int i = 2; i <= n; i++)
            {
                if (is_prime[i])
                {
                    primes[prime_count++] = i;
                    phi[i] = i - 1;
                }
                for (int j = 0; j < prime_count && i * primes[j] <= n; j++)
                {
                    is_prime[i * primes[j]] = false;
                    if (i % primes[j] == 0)
                    {
                        phi[i * primes[j]] = phi[i] * primes[j];
                        break;
                    }
                    else
                    {
                        phi[i * primes[j]] = phi[i] * (primes[j] - 1);
                    }
                }
            }
        }
    }

    // 单独计算一个数的欧拉函数
    int euler_phi(int n)
    {
        int result = n;
        for (int i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                while (n % i == 0)
                    n /= i;
                result -= result / i;
            }
        }
        if (n > 1)
            result -= result / n;
        return result;
    }
}

// =================================================================
// Sorting
// =================================================================
namespace Sorting
{
    // 归并排序
    // arr: 待排序数组, tmp: 辅助数组, l: 左边界, r: 右边界
    void mergeSort(vector<int> &arr, vector<int> &tmp, int l, int r)
    {
        if (l >= r)
            return;
        int mid = (l + r) >> 1;
        mergeSort(arr, tmp, l, mid);
        mergeSort(arr, tmp, mid + 1, r);
        int i = l, j = mid + 1, k = 0;
        while (i <= mid && j <= r)
        {
            if (arr[i] <= arr[j])
                tmp[k++] = arr[i++];
            else
                tmp[k++] = arr[j++];
        }
        while (i <= mid)
            tmp[k++] = arr[i++];
        while (j <= r)
            tmp[k++] = arr[j++];
        for (i = l, k = 0; i <= r; i++, k++)
            arr[i] = tmp[k];
    }

    // 快速排序
    // arr: 待排序数组, l: 左边界, r: 右边界
    void quickSort(vector<int> &arr, int l, int r)
    {
        if (l >= r)
            return;
        int i = l - 1, j = r + 1, x = arr[(l + r) >> 1];
        while (i < j)
        {
            do
                i++;
            while (arr[i] < x);
            do
                j--;
            while (arr[j] > x);
            if (i < j)
                swap(arr[i], arr[j]);
        }
        quickSort(arr, l, j);
        quickSort(arr, j + 1, r);
    }
}

// =================================================================
// Searching
// =================================================================
namespace Searching
{
    // 整数二分查找 (寻找左边界)
    // check(mid): 检查 mid 是否满足条件
    // 区间 [l, r] 被划分成 [l, mid] 和 [mid + 1, r] 时使用
    bool check(int x); // 需要根据具体问题实现
    int binarySearchLeft(int l, int r)
    {
        while (l < r)
        {
            int mid = (l + r) >> 1;
            if (check(mid))
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }

    // 整数二分查找 (寻找右边界)
    // 区间 [l, r] 被划分成 [l, mid - 1] 和 [mid, r] 时使用
    int binarySearchRight(int l, int r)
    {
        while (l < r)
        {
            int mid = (l + r + 1) >> 1;
            if (check(mid))
                l = mid;
            else
                r = mid - 1;
        }
        return l;
    }

    // 实数二分查找
    // eps: 精度要求，通常比题目要求多 2 位
    double binarySearchReal(double l, double r, double eps = 1e-8)
    {
        while (r - l > eps)
        {
            double mid = (l + r) / 2;
            if (check(mid)) // check 函数参数需改为 double
                r = mid;
            else
                l = mid;
        }
        return l;
    }
}

// =================================================================
// Data Structure
// =================================================================
namespace DataStructure
{
    namespace MonotonicStack
    {
        // 单调栈：寻找每个元素右边第一个比它大的元素的索引
        // 如果不存在，则为 -1
        vector<int> nextGreaterElement(const vector<int> &nums)
        {
            int n = nums.size();
            vector<int> res(n, -1);
            stack<int> s; // 存储索引
            for (int i = 0; i < n; ++i)
            {
                while (!s.empty() && nums[s.top()] < nums[i])
                {
                    res[s.top()] = i;
                    s.pop();
                }
                s.push(i);
            }
            return res;
        }
    }

    namespace MonotonicQueue
    {
        // 单调队列：滑动窗口最大值
        vector<int> maxSlidingWindow(const vector<int> &nums, int k)
        {
            deque<int> q; // 存储索引
            vector<int> res;
            for (int i = 0; i < nums.size(); ++i)
            {
                // 移除滑出窗口的元素
                if (!q.empty() && q.front() == i - k)
                {
                    q.pop_front();
                }
                // 保持队列单调递减（队首最大）
                while (!q.empty() && nums[q.back()] < nums[i])
                {
                    q.pop_back();
                }
                q.push_back(i);
                // 记录窗口最大值
                if (i >= k - 1)
                {
                    res.push_back(nums[q.front()]);
                }
            }
            return res;
        }
    }

    namespace Matrix
    {
        // 二维前缀和
        // matrix: 原矩阵 (下标从 1 开始)
        // 返回: 前缀和矩阵 prefix[i][j] 表示 (1,1) 到 (i,j) 的子矩阵和
        vector<vector<long long>> buildPrefixSum2D(const vector<vector<int>> &matrix)
        {
            int n = matrix.size() - 1;
            if (n < 0)
                return {};
            int m = matrix[0].size() - 1;
            vector<vector<long long>> prefix(n + 1, vector<long long>(m + 1, 0));
            for (int i = 1; i <= n; ++i)
            {
                for (int j = 1; j <= m; ++j)
                {
                    prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + matrix[i][j];
                }
            }
            return prefix;
        }

        // 查询子矩阵和
        // prefix: 前缀和矩阵
        // (x1, y1): 左上角, (x2, y2): 右下角
        long long querySubmatrixSum(const vector<vector<long long>> &prefix, int x1, int y1, int x2, int y2)
        {
            return prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1];
        }

        // 二维差分
        // 用于对子矩阵进行区间加减操作
        class DifferenceArray2D
        {
        public:
            int n, m;
            vector<vector<long long>> diff;

            DifferenceArray2D(int rows, int cols) : n(rows), m(cols)
            {
                // 多开一点空间防止越界
                diff.assign(n + 2, vector<long long>(m + 2, 0));
            }

            // 在 (x1, y1) 到 (x2, y2) 的子矩阵加上 val
            void add(int x1, int y1, int x2, int y2, int val)
            {
                diff[x1][y1] += val;
                diff[x1][y2 + 1] -= val;
                diff[x2 + 1][y1] -= val;
                diff[x2 + 1][y2 + 1] += val;
            }

            // 计算最终矩阵 (求前缀和)
            vector<vector<long long>> compute()
            {
                vector<vector<long long>> res(n + 1, vector<long long>(m + 1, 0));
                for (int i = 1; i <= n; ++i)
                {
                    for (int j = 1; j <= m; ++j)
                    {
                        res[i][j] = res[i - 1][j] + res[i][j - 1] - res[i - 1][j - 1] + diff[i][j];
                    }
                }
                return res;
            }
        };
    }

    namespace SegmentTree
    {
        using ll = long long;
        const int N = 1e5 + 5;

        int n;
        vector<ll> arr;
        vector<ll> sum;
        vector<ll> lazy_add;

        void up(int i)
        {
            sum[i] = sum[i << 1] + sum[i << 1 | 1];
        }

        void lazy(int i, ll v, int len)
        {
            sum[i] += v * len;
            lazy_add[i] += v;
        }

        void down(int i, int ln, int rn)
        {
            if (lazy_add[i] != 0)
            {
                lazy(i << 1, lazy_add[i], ln);
                lazy(i << 1 | 1, lazy_add[i], rn);
                lazy_add[i] = 0;
            }
        }

        void build(int l, int r, int i)
        {
            if (l == r)
            {
                sum[i] = arr[l];
                return;
            }
            int mid = (l + r) >> 1;
            build(l, mid, i << 1);
            build(mid + 1, r, i << 1 | 1);
            up(i);
        }

        void add(int jobl, int jobr, ll jobv, int l, int r, int i)
        {
            if (jobl <= l && r <= jobr)
            {
                lazy(i, jobv, r - l + 1);
                return;
            }
            int mid = (l + r) >> 1;
            down(i, mid - l + 1, r - mid);
            if (jobl <= mid)
                add(jobl, jobr, jobv, l, mid, i << 1);
            if (jobr > mid)
                add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
            up(i);
        }

        ll query(int jobl, int jobr, int l, int r, int i)
        {
            if (jobl <= l && r <= jobr)
            {
                return sum[i];
            }

            int mid = (l + r) >> 1;
            down(i, mid - l + 1, r - mid);

            ll ans = 0;
            if (jobl <= mid)
            {
                ans += query(jobl, jobr, l, mid, i << 1);
            }
            if (jobr > mid)
            {
                ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
            }
            return ans;
        }
    }

    namespace Trie
    {
        const int N = 100000;
        int trie[N][26], cnt[N], idx = 1;

        void build(string s)
        {
            int p = 1;
            for (char c : s)
            {
                int u = c - 'a';
                if (!trie[p][u])
                    trie[p][u] = ++idx;
                p = trie[p][u];
            }
            cnt[p]++;
        }

        int query(string s)
        {
            int p = 1, sum = 0;
            for (char c : s)
            {
                int u = c - 'a';
                if (!trie[p][u])
                    break;
                p = trie[p][u];
                sum += cnt[p];
            }
            return sum;
        }

        namespace ZeroOneTrie
        {
            // Note: This uses the same global arrays as Trie above.
            // In a real scenario, you might want separate arrays or reset them.
            void insert(int x)
            {
                int p = 1;
                for (int i = 31; i >= 0; i--)
                {
                    int u = (x >> i) & 1;
                    if (!trie[p][u])
                        trie[p][u] = ++idx;
                    p = trie[p][u];
                }
            }

            int find(int x)
            {
                int p = 1, res = 0;
                for (int i = 31; i >= 0; i--)
                {
                    int u = (x >> i) & 1;
                    int opposite = u ^ 1;
                    if (trie[p][opposite])
                    {
                        res = (res << 1) | 1;
                        p = trie[p][opposite];
                    }
                    else
                    {
                        res = (res << 1);
                        p = trie[p][u];
                    }
                }
                return res;
            }
        }
    }

    namespace UnionFind
    {
        long long find(vector<long long> &parent, long long x)
        {
            if (parent[x] != x)
            {
                parent[x] = find(parent, parent[x]);
            }
            return parent[x];
        }

        void unite(vector<long long> &parent, long long x, long long y)
        {
            long long rootX = find(parent, x);
            long long rootY = find(parent, y);
            if (rootX != rootY)
            {
                parent[rootY] = rootX;
            }
        }
    }



    namespace STTable
    {
        // ST 表 (Sparse Table)
        // 支持静态区间最值查询 (RMQ)
        // 预处理 O(n log n), 查询 O(1)
        const int N = 50005;
        const int LOGN = 20;
        int st1[N][LOGN];
        int st2[N][LOGN];
        int Log[N];
        int n;

        // 初始化
        // a: 输入数组 (下标从 1 开始)
        // size: 数组大小
        void init(const vector<int> &a, int size)
        {
            n = size;
            Log[1] = 0;
            for (int i = 2; i <= n; i++)
                Log[i] = Log[i >> 1] + 1;

            for (int i = 1; i <= n; i++)
            {
                st1[i][0] = a[i];
                st2[i][0] = a[i];
            }

            // 注意：j < LOGN，因为数组第二维大小为 LOGN
            for (int j = 1; j < LOGN; j++)
            {
                for (int i = 1; i + (1 << j) - 1 <= n; i++)
                {
                    // 这里以最大值为例，如果求最小值改为 min
                    st1[i][j] = max(st1[i][j - 1], st1[i + (1 << (j - 1))][j - 1]);
                    st2[i][j] = min(st2[i][j - 1], st2[i + (1 << (j - 1))][j - 1]);
                }
            }
        }

        // 查询区间 [l, r] 的最大值
        int query1(int l, int r)
        {
            int k = Log[r - l + 1];
            return max(st1[l][k], st1[r - (1 << k) + 1][k]);
        }

        int query2(int l, int r)
        {
            int k = Log[r - l + 1];
            return min(st2[l][k], st2[r - (1 << k) + 1][k]);
        }
    }
}

// =================================================================
// Graph
// =================================================================
namespace Graph
{
    int n, m;                // 节点 边
    vector<vector<int>> adj; // 邻接表
    vector<bool> visited;    // 访问标记数组

    // 深度优先搜索
    void dfs(int u)
    {
        visited[u] = true;
        cout << u << " ";
        for (int v : adj[u])
        {
            if (!visited[v])
            {
                dfs(v);
            }
        }
    }

    // 广度优先搜索
    void bfs(int start_node)
    {
        queue<int> q;
        q.push(start_node);
        visited[start_node] = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (int v : adj[u])
            {
                if (!visited[v])
                {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    // 拓扑排序 (Kahn 算法)
    // 返回排序后的节点序列，如果存在环则返回空数组
    // 假设节点编号从 1 到 n
    vector<int> topologicalSort()
    {
        vector<int> in_degree(n + 1, 0);
        for (int u = 1; u <= n; ++u)
        {
            for (int v : adj[u])
            {
                in_degree[v]++;
            }
        }

        queue<int> q;
        for (int i = 1; i <= n; ++i)
        {
            if (in_degree[i] == 0)
            {
                q.push(i);
            }
        }

        vector<int> result;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            result.push_back(u);

            for (int v : adj[u])
            {
                in_degree[v]--;
                if (in_degree[v] == 0)
                {
                    q.push(v);
                }
            }
        }

        if (result.size() != n)
        {
            return {}; // 存在环
        }
        return result;
    }

    namespace ShortestPath
    {
        const int INF = 1e18;

        struct Edge
        {
            int to;
            long long weight;
        };

        // Dijkstra 算法 (堆优化)
        // start: 起点
        // n: 节点数量 (编号 1 到 n)
        // adj: 带权邻接表 vector<vector<Edge>>
        vector<long long> dijkstra(int start, int n, const vector<vector<Edge>> &adj)
        {
            const long long INF = 1e18;
            vector<long long> dist(n + 1, INF);
            dist[start] = 0;

            // pair: {distance, node}
            using PII = pair<long long, int>;
            priority_queue<PII, vector<PII>, greater<PII>> pq;
            pq.push({0, start});

            while (!pq.empty())
            {
                long long d = pq.top().first;
                int u = pq.top().second;
                pq.pop();

                if (d > dist[u])
                    continue;

                for (const auto &e : adj[u])
                {
                    if (dist[u] + e.weight < dist[e.to])
                    {
                        dist[e.to] = dist[u] + e.weight;
                        pq.push({dist[e.to], e.to});
                    }
                }
            }
            return dist;
        }
    }

    // Bellman-Ford Algorithm
    vector<int> bellman_ford(int n, int start, vector<tuple<int, int, int>> &edges)
    {
        vector<int> dist(n, INF);
        dist[start] = 0;

        for (int i = 0; i < n - 1; i++)
        {
            for (auto &[u, v, w] : edges)
            {
                if (dist[u] != INF && dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                }
            }
        }

        // Check for negative weight cycles
        for (auto &[u, v, w] : edges)
        {
            if (dist[u] != INF && dist[u] + w < dist[v])
            {
                throw runtime_error("Graph contains a negative weight cycle");
            }
        }

        return dist;
    }

    // SPFA Algorithm
    vector<int> spfa(int n, int start, vector<vector<pair<int, int>>> &adj)
    {
        vector<int> dist(n, INF);
        vector<bool> in_queue(n, false);
        queue<int> q;

        dist[start] = 0;
        q.push(start);
        in_queue[start] = true;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            in_queue[u] = false;

            for (auto &[v, w] : adj[u])
            {
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    if (!in_queue[v])
                    {
                        q.push(v);
                        in_queue[v] = true;
                    }
                }
            }
        }

        return dist;
    }

    // Kruskal's Algorithm for Minimum Spanning Tree
    struct Kruskal
    {

        struct Edge{
            int u, v, weight;
        };

        vector<Edge> edges;
        vector<int> parent, rank;

        Kruskal(int n)
        {
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; ++i)
                parent[i] = i;
        }

        int find(int x)
        {
            if (parent[x] != x)
            {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void unite(int x, int y)
        {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY)
            {
                if (rank[rootX] < rank[rootY])
                {
                    parent[rootX] = rootY;
                }
                else if (rank[rootX] > rank[rootY])
                {
                    parent[rootY] = rootX;
                }
                else
                {
                    parent[rootY] = rootX;
                    rank[rootX]++;
                }
            }
        }

        int kruskal(int n)
        {
            sort(edges.begin(), edges.end());
            int mst_weight = 0;
            for (const auto &edge : edges)
            {
                if (find(edge.u) != find(edge.v))
                {
                    unite(edge.u, edge.v);
                    mst_weight += edge.weight;
                }
            }
            return mst_weight;
        }

        void addEdge(int u, int v, int weight)
        {
            edges.push_back({u, v, weight});
        }
    };

    // Prim's Algorithm for Minimum Spanning Tree
    struct Prim
    {
        struct Node
        {
            int vertex, weight;
            bool operator>(const Node &other) const
            {
                return weight > other.weight;
            }
        };

        vector<vector<pair<int, int>>> adj;

        Prim(int n)
        {
            adj.resize(n);
        }

        void addEdge(int u, int v, int weight)
        {
            adj[u].emplace_back(v, weight);
            adj[v].emplace_back(u, weight);
        }

        int prim(int start)
        {
            priority_queue<Node, vector<Node>, greater<Node>> pq;
            vector<bool> inMST(adj.size(), false);
            pq.push({start, 0});
            int mst_weight = 0;

            while (!pq.empty())
            {
                auto [u, weight] = pq.top();
                pq.pop();

                if (inMST[u])
                    continue;
                inMST[u] = true;
                mst_weight += weight;

                for (const auto &[v, w] : adj[u])
                {
                    if (!inMST[v])
                    {
                        pq.push({v, w});
                    }
                }
            }
            return mst_weight;
        }
    };
}

// =================================================================
// Dynamic Programming
// =================================================================
namespace DynamicProgramming
{
    namespace Knapsack
    {
        // 0/1 背包
        // n: 物品数量, W: 背包容量
        // w: 物品重量数组 (下标从 1 开始), v: 物品价值数组 (下标从 1 开始)
        int zeroOneKnapsack(int n, int W, const vector<int> &w, const vector<int> &v)
        {
            vector<int> dp(W + 1, 0);
            for (int i = 1; i <= n; ++i)
            {
                for (int j = W; j >= w[i]; --j)
                {
                    dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
                }
            }
            return dp[W];
        }

        // 完全背包
        // n: 物品数量, W: 背包容量
        // w: 物品重量数组, v: 物品价值数组
        int completeKnapsack(int n, int W, const vector<int> &w, const vector<int> &v)
        {
            vector<int> dp(W + 1, 0);
            for (int i = 1; i <= n; ++i)
            {
                for (int j = w[i]; j <= W; ++j)
                {
                    dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
                }
            }
            return dp[W];
        }

        // 多重背包 (二进制拆分优化)
        // n: 物品种数, W: 背包容量
        // w: 重量, v: 价值, c: 数量
        int multipleKnapsack(int n, int W, const vector<int> &w, const vector<int> &v, const vector<int> &c)
        {
            vector<int> new_w, new_v;
            // 重新构建物品列表，下标从 1 开始方便处理（这里直接push_back，使用时注意）
            new_w.push_back(0);
            new_v.push_back(0);

            for (int i = 1; i <= n; ++i)
            {
                int count = c[i];
                for (int k = 1; k <= count; k <<= 1)
                {
                    new_w.push_back(k * w[i]);
                    new_v.push_back(k * v[i]);
                    count -= k;
                }
                if (count > 0)
                {
                    new_w.push_back(count * w[i]);
                    new_v.push_back(count * v[i]);
                }
            }

            int new_n = new_w.size() - 1;
            vector<int> dp(W + 1, 0);
            for (int i = 1; i <= new_n; ++i)
            {
                for (int j = W; j >= new_w[i]; --j)
                {
                    dp[j] = max(dp[j], dp[j - new_w[i]] + new_v[i]);
                }
            }
            return dp[W];
        }

        // 分组背包
        // n: 组数, W: 背包容量
        // groups: groups[i] 存储第 i 组的所有物品，每个物品是 {weight, value}
        struct Item
        {
            int w, v;
        };
        int groupedKnapsack(int n, int W, const vector<vector<Item>> &groups)
        {
            vector<int> dp(W + 1, 0);
            // 遍历每一组
            for (int i = 1; i <= n; ++i)
            {
                // 必须先遍历容量（从大到小），确保每组只选一个
                for (int j = W; j >= 0; --j)
                {
                    // 遍历该组中的每一个物品
                    for (const auto &item : groups[i])
                    {
                        if (j >= item.w)
                        {
                            dp[j] = max(dp[j], dp[j - item.w] + item.v);
                        }
                    }
                }
            }
            return dp[W];
        }
    }
}
