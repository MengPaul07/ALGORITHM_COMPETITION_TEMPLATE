#include <bits/stdc++.h>
using namespace std;
const int N = 200005; const int LOG = 20;
vector<int> adj[N];
int fa[N][LOG]; int dep[N];
// 预处理普通 LCA 的祖先表和节点深度。
void dfs(int u,int f){
    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    for(int i = 1;i < LOG;i++){
        fa[u][i] = fa[fa[u][i-1]][i-1];
    }
    for(auto v:adj[u]){
        if (v == f) continue;
        dfs(v,u);
    }
}
// 用倍增求两个节点的最近公共祖先。
int lca(int x,int y){
    if (dep[x] < dep[y]) swap(x,y);
    // 把 x 跳到和 y 同一深度
    for(int i = LOG-1;i >= 0;i--){
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    }
    if (x == y) return x;
    // 一起向上跳
    for(int i = LOG-1;i >= 0;i--){
        if(fa[x][i] != fa[y][i]){
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}
// 读入一棵树并回答若干次普通 LCA 查询。
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
struct EDGE {
    int v,w;
};
vector<EDGE> adj[N];
int fa[N][LOG]; int mx[N][LOG]; int dep[N];
// 预处理带边权树的祖先表及向上路径最大边权。
void dfs(int u,int f,int w){
    fa[u][0] = f;
    mx[u][0] = w;
    dep[u] = dep[f] + 1;
    for(int i = 1;i < LOG;i++){
        fa[u][i] = fa[fa[u][i-1]][i-1];
        mx[u][i] = max(mx[u][i-1],mx[fa[u][i-1]][i-1]);
    }
    for(auto [v,w]:adj[u]){
        if (v == f) continue;
        dfs(v,u,w);
    }
}
// 查询两点路径上的最大边权。
int qmx(int x,int y){
    int ans = 0;
    if (dep[x] < dep[y]) swap(x,y);
    // 把 x 跳到和 y 同一深度
    for(int i = LOG-1;i >= 0;i--){
        if(dep[fa[x][i]] >= dep[y]){
            ans = max(ans,mx[x][i]);
            x = fa[x][i];
        }
    }
    if (x == y) return ans;
    // 一起向上跳
    for(int i = LOG-1;i >= 0;i--){
        if(fa[x][i] != fa[y][i]){
            ans = max(ans,mx[x][i]);
            ans = max(ans,mx[y][i]);
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    ans = max(ans,mx[x][0]);
    ans = max(ans,mx[y][0]);
    return ans;
}
