#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin>>n;

    int tmp=0;

    for (int i = 5; i <=n;i*=5){
        tmp += n / i;
    }
    cout << tmp;

    return 0;
}