#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200005; const int M = 400005;
struct Edge{ int u,v,w; } edge[M];
int fa[N];
vector<pair<int,int>> graph[N];
// 查找并查集代表，并进行路径压缩。
int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
// 合并两个连通块，返回是否真的发生了合并。
bool merge(int x, int y){
    x = find(x); y = find(y);
    if(x == y)return false;
    fa[x] = y;
    return true;
}
// edge[0..m-1] 用 1..n 编号，O(m log m)
// 用 Kruskal 算法求最小生成树，不连通时返回 -1。
int kruskal(int n, int m){
    for(int i = 1;i <= n;i++)fa[i] = i;
    sort(edge,edge + m,[](Edge a,Edge b){ return a.w < b.w; });
    int ans = 0,cnt = 0;
    for(int i = 0;i < m;i++)
        if (merge(edge[i].u,edge[i].v)) ans += edge[i].w,cnt++;
    return cnt == n - 1 ? ans : -1;
}
// 向 Prim 使用的无向邻接表添加一条带权边。
void addEdge(int u, int v, int w){
    graph[u].push_back({v,w});
    graph[v].push_back({u,w});
}
// 从 start 出发用 Prim 算法求最小生成树，不连通时返回 -1。
int prim(int n, int start = 1){
    vector<int> vis(n + 1);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    q.push({0,start});
    int ans = 0,cnt = 0;
    while(!q.empty()){
        auto [w,u] = q.top(); q.pop();
        if(vis[u])continue;
        vis[u] = 1; ans += w; cnt++;
        for(auto [v,nw] : graph[u])
            if(!vis[v])q.push({nw,v});
    }
    return cnt == n ? ans : -1;
}
