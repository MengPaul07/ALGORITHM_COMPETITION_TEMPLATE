#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1); 
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    vector<vector<int>> dp(n + 1, vector<int>(m + 2, 0));

    if (a[1] == 0)
    {
        for (int x = 1; x <= m; x++)
            dp[1][x] = 1;
    }
    else
    {
        dp[1][a[1]] = 1;
    }

    for (int i = 2; i <= n; i++)
    {
        int L = 1, R = m;
        if (a[i] != 0)
            L = R = a[i];

        for (int x = L; x <= R; x++)
        {
            long long ways = 0;
            if (x > 1)
                ways += dp[i - 1][x - 1];
            ways += dp[i - 1][x];
            if (x < m)
                ways += dp[i - 1][x + 1];
            dp[i][x] = ways % MOD;
        }
    }

    long long ans = 0;
    for (int x = 1; x <= m; x++)
        ans += dp[n][x];
    cout << ans % MOD << endl;

    return 0;
}