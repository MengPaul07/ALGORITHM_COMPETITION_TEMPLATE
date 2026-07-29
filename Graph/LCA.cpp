#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()

const int N = 200005;
const int LOG = 20;

vector<int> adj[N];
int fa[N][LOG];
int dep[N];

void dfs(int u,int f){
    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    for(int i = 1;i < LOG;i++){
        fa[u][i] = fa[fa[u][i-1]][i-1];
    }
    for(auto v:adj[u]){
        if(v == f)
            continue;
        dfs(v,u);
    }
}


int lca(int x,int y){
    if(dep[x] < dep[y])
        swap(x,y);
    // 把 x 跳到和 y 同一深度
    for(int i = LOG-1;i >= 0;i--){
        if(dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    }
    if(x == y)
        return x;

    // 一起向上跳
    for(int i = LOG-1;i >= 0;i--){
        if(fa[x][i] != fa[y][i]){
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}



void solve(){
    int n;
    cin >> n;
    for(int i = 1;i < n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    int q;
    cin >> q;
    while(q--){
        int x,y;
        cin >> x >> y;
        cout << lca(x,y) << endl;
    }
}


signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int t = 1;
    // cin >> t;
    while(t--)
        solve();
    return 0;
}