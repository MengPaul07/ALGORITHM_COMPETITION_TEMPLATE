#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> v(n),dp(m+5);
    dp[0] = 1;
    
    for(auto &i:v)
        cin >> i;

    for (int i = 1; i <= m;i++){
        for (int j = 0; j < n;j++){
            if (i - v[j] >= 0)
            {
                dp[i] = (dp[i]+dp[i-v[j]]) % MOD;
            }
        }
    }
    cout << dp[m];
    return 0;
}