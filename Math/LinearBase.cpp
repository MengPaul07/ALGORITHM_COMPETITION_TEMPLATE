#include <bits/stdc++.h>
using namespace std;

vector<int> p(64),pos(N);

void insert(int x,int id){
    for(int i = 62;i >= 0;i--){
        if((x >> i & 1) == 0)continue;
        if(!p[i]){
            p[i] = x;
            pos[i] = id;
            return;
        }

        if(pos[i] < id){
            swap(pos[i],id);
            swap(p[i],x);
        }
        x ^= p[i];
    }
}



void solve(){
    int n;cin >> n;
    vector<int> a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        insert(a[i]);
    }

    int ans = 0;
    for(int i = 62;i >= 0;i--){
        ans = max(ans,ans^p[i]);
    }
    cout << ans << endl;
}

