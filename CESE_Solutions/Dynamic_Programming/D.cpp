#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    vector<int> dp(m + 1, 0);
    dp[0] = 1;

    for (auto &i : v)
        cin >> i;

    for (int j = 0; j < n; j++)
    { 
        for (int i = v[j]; i <= m; i++)
        { 
            dp[i] = (dp[i] + dp[i - v[j]]) % MOD;
        }
    }

    
    cout << dp[m];
    return 0;
}