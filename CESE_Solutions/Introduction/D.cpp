#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t,ans;
    scanf("%lld",&t);
    while(t--){
        int x,y;
        scanf("%lld %lld", &x, &y);
        int m = max(x, y);
        if(m%2==0)
            ans = (m - 1) * (m - 1) + x + m - y;
        else
            ans = (m - 1) * (m - 1) + y + m - x;
        printf("%lld\n", ans);
        }

        return 0;
}