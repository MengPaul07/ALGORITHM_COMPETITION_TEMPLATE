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