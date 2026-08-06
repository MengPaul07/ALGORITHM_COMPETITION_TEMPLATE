namespace STTable
{
    // ST 表 (Sparse Table)
    // a 下标从 1 开始；支持 O(1) 查询区间最值
    const int N = 50005;
    const int LOGN = 20;
    int stMax[N][LOGN];
    int stMin[N][LOGN];
    int lg2v[N];
    int n;

    void init(const vector<int> &a, int size)
    {
        n = size;
        lg2v[1] = 0;
        for (int i = 2; i <= n; i++)
            lg2v[i] = lg2v[i >> 1] + 1;

        for (int i = 1; i <= n; i++)
        {
            stMax[i][0] = a[i];
            stMin[i][0] = a[i];
        }

        for (int j = 1; j < LOGN; j++)
        {
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
            {
                stMax[i][j] = max(stMax[i][j - 1], stMax[i + (1 << (j - 1))][j - 1]);
                stMin[i][j] = min(stMin[i][j - 1], stMin[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int queryMax(int l, int r)
    {
        int k = lg2v[r - l + 1];
        return max(stMax[l][k], stMax[r - (1 << k) + 1][k]);
    }

    int queryMin(int l, int r)
    {
        int k = lg2v[r - l + 1];
        return min(stMin[l][k], stMin[r - (1 << k) + 1][k]);
    }
}
