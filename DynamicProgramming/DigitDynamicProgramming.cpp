#include <bits/stdc++.h>
using namespace std;

// Windy’s number
void solve(){
    int a,b;
    cin >> a >> b;
    vector<int> num(20);
    
    vector<vector<int>> dp(20,vector<int>(15,-1));


    auto dfs = [&](auto dfs,int pos,int last,bool limit,bool zero) -> int {
        if(pos == 0)return 1;

        if(!zero && !limit && dp[pos][last] != -1){
            return dp[pos][last];
        }

        int res = 0 ;

        int lim = (limit)?num[pos] : 9;

        for(int i = 0;i <= lim;i++){
            if(!zero && abs(i - last) < 2)continue;
            
            res += dfs(dfs,pos - 1,(zero && i == 0)?0:i,limit && i == lim,zero && i == 0);
        }

        if(!limit && !zero){
            dp[pos][last] = res;
        }
        return res;


    };

    auto cal = [&](int x){
        int len = 0;
        while(x){
            num[++len]=x%10;
            x/=10;
        }

        return dfs(dfs,len,0,1,1);
    };

    cout << cal(b) - cal(a - 1) << endl;    
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}