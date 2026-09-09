#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 200005;

int a[N];
int ls[N], rs[N];
int stk[N], top;
int root;

// 小根笛卡尔树，按下标 1..n 建树
void buildCartesian(int n)
{
    fill(ls + 1, ls + n + 1, 0);
    fill(rs + 1, rs + n + 1, 0);

    root = 0;
    top = 0;

    for (int i = 1; i <= n; i++)
    {
        int last = 0;
        while (top && a[stk[top]] > a[i])
            last = stk[top--];

        ls[i] = last;
        if (top)
            rs[stk[top]] = i;
        else
            root = i;

        stk[++top] = i;
    }
}
