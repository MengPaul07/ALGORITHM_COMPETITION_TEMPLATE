#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1005;

int a[N][N];
int pre[N][N];
int diff[N][N];

// 二维前缀和
void buildPrefix(int n, int m)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1]
                      - pre[i - 1][j - 1] + a[i][j];
        }
    }
}

int queryPrefix(int x1, int y1, int x2, int y2)
{
    return pre[x2][y2] - pre[x1 - 1][y2]
         - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1];
}

// 二维差分：给矩形 [x1, x2] * [y1, y2] 加 val
void addRect(int x1, int y1, int x2, int y2, int val)
{
    diff[x1][y1] += val;
    diff[x1][y2 + 1] -= val;
    diff[x2 + 1][y1] -= val;
    diff[x2 + 1][y2 + 1] += val;
}

// 还原差分数组；结果仍保存在 diff_ 中
void buildDiff(int n, int m)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            diff[i][j] += diff[i - 1][j] + diff[i][j - 1]
                        - diff[i - 1][j - 1];
        }
    }
}
