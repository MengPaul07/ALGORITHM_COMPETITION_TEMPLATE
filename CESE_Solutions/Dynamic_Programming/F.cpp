#include <bits/stdc++.h>
using namespace std;

char g[1005][1005];
long long dp[1005][1005]; 
const int MOD = 1e9 + 7;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i <= n + 1; i++)
    {
        for (int j = 0; j <= n + 1; j++)
        {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> g[i][j];
        }
    }

    if (g[1][1] == '*' || g[n][n] == '*')
    {
        cout << 0;
        return 0;
    }

    dp[1][1] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (g[i][j] == '*')
                continue;

            if (i > 1 && g[i - 1][j] != '*')
            {
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            }

            if (j > 1 && g[i][j - 1] != '*')
            {
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            }
        }
    }   

    cout << dp[n][n];
    return 0;
}