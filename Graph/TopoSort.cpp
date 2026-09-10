#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200005;
vector<int> graph[N],topo;
int deg[N];
// 清空图、入度数组和上一次得到的拓扑序。
void initGraph(int n){
    topo.clear();
    for(int i = 1;i <= n;i++)graph[i].clear(),deg[i] = 0;
}
// 添加有向边 u -> v，并维护 v 的入度。
void addEdge(int u, int v){
    graph[u].push_back(v);
    deg[v]++;
}
// Kahn 算法求拓扑序，成功时结果保存在 topo 中。
bool topoSort(int n){
    queue<int> q;
    for(int i = 1;i <= n;i++)if(!deg[i])q.push(i);
    while(!q.empty()){
        int u = q.front(); q.pop();
        topo.push_back(u);
        for(int v : graph[u])if(!--deg[v])q.push(v);
    }
    return (int)topo.size() == n;
}
