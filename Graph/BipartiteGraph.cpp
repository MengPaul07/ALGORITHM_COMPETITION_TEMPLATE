#include <bits/stdc++.h>
using namespace std;
namespace BipartiteColoring {
    const int SIZE = 100000 + 10;
    vector<int> edge[SIZE];
    int color[SIZE]; // -1: uncolored, 0/1: two parts
    // 清空前 n 个点的邻接表，并将颜色恢复为未染色。
    void init(int n) {
        for (int i = 1; i <= n; i++) edge[i].clear();
        memset(color, -1, sizeof(color));
    }
    // 添加一条无向边，用于二分图染色判定。
    void addEdge(int u, int v) {
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    // 从 u 开始染色；若发现同色相邻点则返回 false。
    bool dfs(int u, int c) {
        color[u] = c;
        for (auto v : edge[u]) {
            if (color[v] == -1) {
                if (!dfs(v, c ^ 1)) return false;
            }
            else if (color[v] == c) {
                return false;
            }
        }
        return true;
    }
    // 检查 1..n 的整个图是否为二分图。
    bool check(int n) {
        for (int i = 1; i <= n; i++) {
            if (color[i] == -1) {
                if (!dfs(i, 0)) return false;
            }
        }
        return true;
    }
}
// matching
// 用增广路算法求二分图最大匹配数。
void solve(){
    int n,m,e;cin >> n >> m >> e;
    vector<vector<int>> adj(n + m + 1);
    for(int i = 0;i < e;i++){
        int u,v;
        cin >> u >> v;
        adj[u]. push_back(v);       
    }
    vector<int> vis(n + m + 1);
    vector<int> match(n + m + 1);
    auto find = [&](auto find,int u) -> bool {
        for(auto v : adj[u]){
            if(vis[v])continue;
            vis[v] = 1;
            if(match[v] == 0 || find(find,match[v])){
                match[v] = u;
                return 1;
            }
        }
        return 0;
    };
    int cnt = 0;
    for(int i = 1;i <= n;i++){
        vis.assign(n + m + 1,0);
        if(find(find,i))cnt++;
    }
    cout << cnt << endl;
}
