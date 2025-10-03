#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin>>n;
    vector<pair<int, int>> vp;
    for (int i = 0;i<n;i++){
        int a,b;
        cin>>a>>b;
        vp.push_back({a, b});
    }

    sort(vp.begin(), vp.end(), [](const pair<int, int> &x, const pair<int, int> &y)
         {return x.second < y.second;});
    
    int cnt = 1;
    int last = 0;
    for (int i = 1; i < vp.size();i++){
        if(vp[last].second<=vp[i].first){
            last = i;
            cnt++;
        }
    }
    cout << cnt;

    return 0;
}