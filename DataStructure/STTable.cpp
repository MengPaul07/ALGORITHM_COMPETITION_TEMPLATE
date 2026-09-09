#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 200005;
const int LOG = 20;

int a[N];
int stMax[N][LOG], stMin[N][LOG];
int lg2_[N];

void initST(int n)
{
    lg2_[1] = 0;
    for (int i = 2; i <= n; i++)
        lg2_[i] = lg2_[i >> 1] + 1;

    for (int i = 1; i <= n; i++)
        stMax[i][0] = stMin[i][0] = a[i];

    for (int j = 1; j < LOG; j++)
    {
        for (int i = 1; i + (1LL << j) - 1 <= n; i++)
        {
            stMax[i][j] = max(stMax[i][j - 1],
                              stMax[i + (1LL << (j - 1))][j - 1]);
            stMin[i][j] = min(stMin[i][j - 1],
                              stMin[i + (1LL << (j - 1))][j - 1]);
        }
    }
}

int queryMax(int l, int r)
{
    int k = lg2_[r - l + 1];
    return max(stMax[l][k], stMax[r - (1LL << k) + 1][k]);
}

int queryMin(int l, int r)
{
    int k = lg2_[r - l + 1];
    return min(stMin[l][k], stMin[r - (1LL << k) + 1][k]);
}
