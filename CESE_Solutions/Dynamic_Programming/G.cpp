#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,p;
    cin >> n >> p;

    vector<int> v1(n);//price
    vector<int> v2(n);//pages
    vector<int> dp(p + 1,0);

    for(auto &a:v1)
        cin >> a;
    
    for(auto &a:v2)
        cin >> a;

    for (int i = n - 1; i >= 0;i--)
        for (int j = p; j >= v1[i];j--){
            dp[j] = max(dp[j], dp[j - v1[i]] + v2[i]);
        }

    cout << dp[p];
    return 0;
}

/*
    1   2   3   4   5   6   7   8   9   10

    3   3   3   3   3   3   3   3   3   3
                    8   8   8   8   8   8
                                        
*/