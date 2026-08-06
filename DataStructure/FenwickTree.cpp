int lowbit(int x)
{
    return x & (-x);
}

 namespace FenwickTree
{
    // 树状数组 (Binary Indexed Tree)
    // 支持单点修改和区间查询
    const int N = 200005;
    int tree[N];
    int n;


    // 单点更新：index 位置加上 delta
    void add(int index, int delta)
    {
        for (int i = index; i <= n; i += lowbit(i))
        {
            tree[i] += delta;
        }
    }

    // 查询前缀和：[1, index]
    int ask(int index)
    {
        int sum = 0;
        for (int i = index; i > 0; i -= lowbit(i))
        {
            sum += tree[i];
        }
        return sum;
    }

    // 查询区间和：[left, right]
    int query(int left, int right)
    {
        return ask(right) - ask(left - 1);
    }
}


namespace FenwickTree2D
{
    // 二维树状数组 (2D Binary Indexed Tree)
    // 支持单点修改和矩形区域查询
    const int N = 505;
    int tree[N][N];
    int n, m;

    // 初始化
    void init(int rows, int cols)
    {
        n = rows;
        m = cols;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                tree[i][j] = 0;
    }

    // 单点更新：在 (x, y) 位置加上 delta
    void add(int x, int y, int delta)
    {
        for (int i = x; i <= n; i += lowbit(i))
        {
            for (int j = y; j <= m; j += lowbit(j))
            {
                tree[i][j] += delta;
            }
        }
    }

    // 查询前缀和：[1, 1] 到 (x, y)
    int ask(int x, int y)
    {
        int sum = 0;
        for (int i = x; i > 0; i -= lowbit(i))
        {
            for (int j = y; j > 0; j -= lowbit(j))
            {
                sum += tree[i][j];
            }
        }
        return sum;
    }

    // 查询矩形区域和：[x1, y1] 到 [x2, y2]
    int query(int x1, int y1, int x2, int y2)
    {
        return ask(x2, y2) - ask(x1 - 1, y2) - ask(x2, y1 - 1) + ask(x1 - 1, y1 - 1);
    }
}


// 使用树状数组离线查询第k小的元素
// 需要先对元素进行离散化，更新时在离散化后的索引位置更新，查询时根据树状数组的前缀和来找到第k小的元素位置
namespace FenwickTreeKth
{
    const int N = 1e5 + 5;
    int tree[N];

    void update(int index, int delta, int n)
    {
        for (int i = index; i <= n; i += lowbit(i))
        {
            tree[i] += delta;
        }
    }

    // 查询第 k 小的元素位置
    int find(int k, int n)
    {
        int pos = 0;
        for (int i = 1 << 17; i > 0; i >>= 1)
        {
            int next_pos = pos + i;
            if (next_pos <= n && tree[next_pos] < k)
            {
                pos = next_pos;
                k -= tree[pos];
            }
        }
        return pos + 1;
    }

    void solve(){
        // 示例用法
        int n; // 离散化后的元素个数
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            update(arr[i], 1, n); // 更新树状数组
        }

        int q; // 查询次数
        cin >> q;
        while (q--)
        {
            int k;
            cin >> k;
            int pos = find(k, n); // 查询第 k 小的元素位置
            cout << pos << endl; // 输出结果
        }
    }
}