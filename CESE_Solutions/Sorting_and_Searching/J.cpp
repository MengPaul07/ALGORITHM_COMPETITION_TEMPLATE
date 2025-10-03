#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n),vc(n+1);
    for (int i = 0; i < n;i++){
        cin >> v[i];
        vc[v[i]] = i+1;
    }
    
    int cnt = 1;
    for (int i = 2; i <= n; i++)
    {
        if(vc[i]<vc[i-1]){
            cnt++;
        };
    }

    for(auto a:vc)
        cout << a;
    cout << endl;

    cout << cnt;
    return 0;
}
