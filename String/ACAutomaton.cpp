#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5; int cnt[N]; int tr[N][26]; int fail[N]; int tot;
// 插入一个模式串，并记录它在 Trie 终点出现的次数。
void insert(string s){
    int u = 0;
    for(auto ch : s){
        int c = ch - 'a';
        if (!tr[u][c]) tr[u][c] = ++tot;
        u = tr[u][c];
    }
    cnt[u]++;
}
// 用 BFS 建立失配指针，并补齐自动机的转移边。
void build(){
    queue<int> q;
    for(int c = 0;c < 26;c++){
        if (tr[0][c]) q.push(tr[0][c]);
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int c = 0;c < 26;c++){
            if(tr[u][c]){
                fail[tr[u][c]] = tr[fail[u]][c];
                q.push(tr[u][c]);
            }
            else{
                tr[u][c] = tr[fail[u]][c];
            }
        }
    }
}
// 建立 AC 自动机并扫描文本，统计所有模式串的匹配次数。
void solve(){
    int n;cin >> n;
    for(int i = 0;i < n;i++){
        string s; cin >> s;
        insert(s);
    }
    build();
    string s;cin >> s; int u = 0;int ans = 0;
    for(auto ch : s){
        int c = ch - 'a';
        u = tr[u][c];
        for(int p = u;p;p = fail[p]){
            if (cnt[p] == -1) break;
            ans += cnt[p];
            cnt[p] = -1;
        }
    }
    cout << ans << endl;
}
