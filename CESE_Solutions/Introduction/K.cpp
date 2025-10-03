#include <bits/stdc++.h>
using namespace std;
#define int long long

int cnt = 0;

void hc(int n, int a, int b, int c)
{
    if (n == 0)
        return;
    hc(n - 1, a, c, b);
    hc(n - 1, b, a, c);
    cnt++;
}

void hc1(int n, int a, int b, int c)
{
    if (n == 0)
        return;
    hc1(n - 1, a, c, b);
    printf("%lld %lld\n", a, c);
    hc1(n - 1, b, a, c);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    scanf("%d", &n);
    hc(n, 1, 2, 3);
    printf("%lld\n", cnt);
    hc1(n, 1, 2, 3);

    return 0;
}