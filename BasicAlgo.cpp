namespace Matrix
{
    // 二维前缀和
    // matrix: 原矩阵 (下标从 1 开始)
    // 返回: 前缀和矩阵 prefix[i][j] 表示 (1,1) 到 (i,j) 的子矩阵和
    vector<vector<int>> buildPrefixSum2D(const vector<vector<int>> &matrix)
    {
        int n = matrix.size() - 1;
        if (n < 0)
            return {};
        int m = matrix[0].size() - 1;
        vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));
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
    int querySubmatrixSum(const vector<vector<int>> &prefix, int x1, int y1, int x2, int y2)
    {
        return prefix[x2][y2] - prefix[x1 - 1][y2] - prefix[x2][y1 - 1] + prefix[x1 - 1][y1 - 1];
    }

    // 二维差分
    // 用于对子矩阵进行区间加减操作
    class DifferenceArray2D
    {
    public:
        int n, m;
        vector<vector<int>> diff;

        DifferenceArray2D(int rows, int cols) : n(rows), m(cols)
        {
            // 多开一点空间防止越界
            diff.assign(n + 2, vector<int>(m + 2, 0));
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
        vector<vector<int>> compute()
        {
            vector<vector<int>> res(n + 1, vector<int>(m + 1, 0));
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