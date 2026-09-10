#include <bits/stdc++.h>
using namespace std;

const int INF = (1LL << 62);
struct Edge {
    int v,cap,rev;
};
struct Dinic{
    int n,s,t;
    vector<vector<Edge>> adj;
    vector<int> dep,cur;
    // 初始化 n 个点、源点 s 和汇点 t 的网络流图。
    Dinic(int n,int s,int t):n(n),s(s),t(t){
        adj.resize(n + 1);dep.resize(n + 1);cur.resize(n + 1);
    }
    // 添加容量为 w 的有向边，同时建立反向边。
    void addEdge(int u,int v,int w){
        Edge a = {v,w,(int)adj[v].size()};
        Edge b = {u,0,(int)adj[u].size()};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }
    // 在残量网络上分层，判断汇点是否仍然可达。
    bool bfs(){
        fill(all(dep),-1);
        queue<int> q;q.push(s);
        dep[s] = 0;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(auto e : adj[u]){
                if(e.cap > 0 && dep[e.v] == -1){
                    dep[e.v] = dep[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return dep[t] != -1;
    }
    // 沿分层图从 u 推送不超过 flow 的阻塞流。
    int dfs(int u,int flow){
        if(u == t)return flow;
        for(int &i = cur[u];i < sz(adj[u]);i++){
            Edge &e = adj[u][i];
            if(e.cap <= 0)continue;
            if(dep[e.v] != dep[u] + 1)continue;
            int x = dfs(e.v,min(flow,e.cap));
            if(x == 0)continue;
            e.cap -= x;
            adj[e.v][e.rev].cap += x;
            return x;
        }
        return 0;
    }
    // 不断构造分层图并增广，返回最大流。
    int maxFlow(){
        int ans = 0;
        while(bfs()){
            fill(all(cur),0);
            while(int flow = dfs(s,INF)){
                ans += flow;
            }
        }
        return ans;
    }
};
// 读入有向容量网络并输出最大流。
void solve(){
    int n,m,s,t;cin >> n >> m >> s >> t;
    Dinic dinic(n,s,t);
    for(int i = 0;i < m;i++){
        int u,v,w;cin >> u >> v >> w;
        dinic.addEdge(u,v,w);
    }
    cout << dinic.maxFlow() << endl;
}
