#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 200005;

int a[N];
int nxt[N];
int stk[N], top;
int windowMax[N];
int que[N], head, tail;

// 每个位置右侧第一个严格更大的位置；不存在时为 -1
void nextGreater(int n)
{
    top = 0;
    for (int i = n; i >= 1; i--)
    {
        while (top && a[stk[top]] <= a[i])
            top--;
        nxt[i] = top ? stk[top] : -1;
        stk[++top] = i;
    }
}

// 滑动窗口最大值，结果保存在 windowMax[1..n-k+1]
void slidingWindowMax(int n, int k)
{
    head = tail = 1;
    for (int i = 1; i <= n; i++)
    {
        while (head < tail && que[head] <= i - k)
            head++;
        while (head < tail && a[que[tail - 1]] <= a[i])
            tail--;

        que[tail++] = i;
        if (i >= k)
            windowMax[i - k + 1] = a[que[head]];
    }
}
