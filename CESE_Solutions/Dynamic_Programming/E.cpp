#include <bits/stdc++.h>
using namespace std;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> digit,dp(n+1,0);
    dp[0] = 0;
    for (int i = 1; i <= n;i++){
        int tmp = i;
        int maxn = 0;
        while(tmp>0){
            int dtmp = tmp % 10;
            tmp /= 10;
            maxn = max(maxn, dtmp);
        }
        
        dp[i] = dp[i-maxn] + 1;
    }

    cout << dp[n];
    return 0;
}



// 35 30 27 
// 100 99 90 81 73 66 60 54 49 40 36 30 27 20 18 
// 32 29 20

