#include <bits/stdc++.h>
using namespace std;
vector<int> p(64),pos(N);
// 将带编号 id 的数 x 插入线性基，并维护编号较新的表示。
void insert(int x,int id){
    for(int i = 62;i >= 0;i--){
        if((x >> i & 1) == 0)continue;
        if(!p[i]){
            p[i] = x;pos[i] = id;
            return;
        }
        if(pos[i] < id){
            swap(pos[i],id);
            swap(p[i],x);
        }
        x ^= p[i];
    }
}
// 建立线性基并求所有输入数异或出的最大值。
void solve(){
    int n;cin >> n;
    vector<int> a(n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        insert(a[i],i);
    }
    int ans = 0;
    for(int i = 62;i >= 0;i--){
        ans = max(ans,ans^p[i]);
    }
    cout << ans << endl;
}
