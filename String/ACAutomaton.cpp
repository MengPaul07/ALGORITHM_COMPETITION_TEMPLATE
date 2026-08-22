#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int cnt[N];
int tr[N][26];
int fail[N];
int tot;

void insert(string s){
    int u = 0;
    for(auto ch : s){
        int c = ch - 'a';
        if(!tr[u][c]){
            tr[u][c] = ++tot;
        }

        u = tr[u][c];
    }
    cnt[u]++;
}

void build(){
    queue<int> q;

    for(int c = 0;c < 26;c++){
        if(tr[0][c]){
            q.push(tr[0][c]);
        }
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

void solve(){
    int n;cin >> n;
    for(int i = 0;i < n;i++){
        string s; cin >> s;
        insert(s);
    }

    build();
    string s;cin >> s;

    int u = 0;int ans = 0;

    for(auto ch : s){
        int c = ch - 'a';
        u = tr[u][c];

        for(int p = u;p;p = fail[p]){
            if(cnt[p] == -1){
                break;
            }
            ans += cnt[p];
            cnt[p] = -1;
        }
    }

    cout << ans << endl;
}

