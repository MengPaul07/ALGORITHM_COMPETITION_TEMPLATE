#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    int a, b;
    scanf("%lld", &t);
    while(t--){
        scanf("%lld %lld", &a, &b);
        if(a>2*b||b>2*a)
            printf("NO\n");
        else 
            if((a+b)%3==0)
                printf("YES\n");
            else
                printf("NO\n");
    }

    return 0;
}