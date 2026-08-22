#include <bits/stdc++.h>
using namespace std;


// Tarjan 割点
struct Edge{
    int v,id;
};

void solve(){
    int n,m;cin >> n >> m;
    vector<vector<Edge>> adj(n + 1);
    for(int i = 1;i <= m;i++){
        int u, v;cin >> u >> v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }

    vector<int> dfn(n + 1),low(n + 1),cut(n + 1);

    int p = 0;

    function<void(int,int)> tarjan;

    tarjan = [&](int u,int pe){
        dfn[u] = low[u] = ++p;

        int child = 0;
        for(auto [v,id] : adj[u]){
            if(id == pe)continue;

            if(!dfn[v]){
                child++;

                tarjan(v,id);
                low[u] = min(low[u],low[v]);

                if(pe != -1 && low[v] >= dfn[u]){
                    cut[u] = 1;
                }
            }
            else{
                low[u] = min(low[u],dfn[v]);
            }
        }
        if(pe == -1 && child >= 2){
            cut[u] = 1;
        }
    };

    for(int i = 1;i <= n;i++){
        if(!dfn[i]){
            tarjan(i,-1);
        }
    }

    int cnt = 0;
    for(int i = 1;i <= n;i++){
        cnt += cut[i];
    }
    cout << cnt << endl;
 
    for(int i = 1;i <= n;i++){
        if(cut[i]){
            cout << i << " ";
        }
    }cout << endl;

}

// tarjan 缩点 从 1 - n 最大和

void solve(){
    int n,m;cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1;i <= n;i++)cin >> a[i];
    vector<vector<int>> adj(n + 1);
    for(int i = 0;i < m;i++){
        int u,v;cin >> u >> v;
        adj[u].push_back(v);
    }

    vector<int> dfn(n + 1),low(n + 1),in(n + 1),belong(n + 1);

    vector<int> st;
    int p = 0;int cnt = 0;
    function<void(int)> tarjan;
    tarjan = [&](int u){
        dfn[u] = low[u] = ++p;
        st.push_back(u);
        in[u] = 1;
        for(auto v : adj[u]){
            if(!dfn[v]){
                tarjan(v);
                low[u] = min(low[u],low[v]);
            }
            else if(in[v]){
                low[u] = min(low[u],dfn[v]);
            }
        }
        
        if(low[u] == dfn[u]){
            cnt++;
            while(1){
                int v = st.back();
                st.pop_back();

                in[v] = 0;
                belong[v] = cnt;

                if(v == u)break;
            }
        }
    };


    for(int i = 1;i <= n;i++){
        if(!dfn[i])tarjan(i);
    }

    vector<int> w(cnt + 1);

    for(int i = 1;i <= n;i++){
        w[belong[i]] += a[i];
    }

    vector<vector<int>> dag(cnt + 1);
    vector<int> deg(n + 1);

    for(int u = 1;u <= n;u++){
        for(auto v : adj[u]){
            int x = belong[u],y = belong[v];
            if(x == y)continue;
            dag[x].push_back(y);
            deg[y]++;
        }
    }

    vector<int> dp(cnt + 1,-INF);
    dp[belong[1]] = w[belong[1]];


    queue<int> q;

    for(int i = 1;i <= cnt;i++){
        if(deg[i] == 0){
            q.push(i);
        }
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(auto v : dag[u]){
            if(dp[u] != -INF){
                dp[v] = max(dp[v],dp[u] + w[v]);
            }

            deg[v]--;

            if(deg[v] == 0){
                q.push(v);
            }
        }
    }

    cout << dp[belong[n]] << endl;
}



// 点双
void solve(){
    int n,m;cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n + 1);

    for(int i = 1;i <= m;i++){
        int u,v;cin >> u >> v;

        // 自环不增加新的点
        if(u == v)continue;

        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }

    vector<int> dfn(n + 1),low(n + 1);
    vector<int> st;
    vector<vector<int>> ans;

    int timer = 0;

    function<void(int,int)> tarjan;
    tarjan = [&](int u,int inEdge){
        dfn[u] = low[u] = ++timer;
        st.push_back(u);

        for(auto [v,id] : adj[u]){
            // 不能只判断 v == fa，因为可能有重边
            if(id == inEdge)continue;

            if(!dfn[v]){
                tarjan(v,id);

                low[u] = min(low[u],low[v]);

                if(low[v] >= dfn[u]){
                    vector<int> cur;

                    while(1){
                        int x = st.back();
                        st.pop_back();
                        cur.push_back(x);
                        if(x == v)break;
                    }
                    cur.push_back(u);
                    ans.push_back(cur);
                }
            }
            else if(dfn[v] < dfn[u]){
                // 只处理指向祖先的返祖边
                low[u] = min(low[u],dfn[v]);
            }
        }
    };

    for(int i = 1;i <= n;i++){
        if(dfn[i])continue;

        tarjan(i,-1);

        // 根节点不会被上面的条件弹出
        if(!st.empty() && st.back() == i){
            st.pop_back();
        }

        // 孤立点，或者只有自环的点
        if(adj[i].empty()){
            ans.push_back({i});
        }
    }

    cout << ans.size() << endl;

    for(auto &cur : ans){
        cout << cur.size() << " ";

        for(auto x : cur){
            cout << x << " ";
        }

        cout << endl;
    }
}


void solve(){
    int n,m;cin >> n >> m;

    vector<vector<pair<int,int>>> adj(n + 1);

    for(int i = 1;i <= m;i++){
        int u,v;cin >> u >> v;

        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }

    vector<int> dfn(n + 1),low(n + 1);
    vector<int> bridge(m + 1);
    int timer = 0;

    function<void(int,int)> tarjan;
    tarjan = [&](int u,int inEdge){
        dfn[u] = low[u] = ++timer;

        for(auto [v,id] : adj[u]){
            if(id == inEdge)continue;

            if(!dfn[v]){
                tarjan(v,id);

                low[u] = min(low[u],low[v]);

                // 注意：边双是严格大于
                if(low[v] > dfn[u]){
                    bridge[id] = 1;
                }
            }
            else if(dfn[v] < dfn[u]){
                low[u] = min(low[u],dfn[v]);
            }
        }
    };

    for(int i = 1;i <= n;i++){
        if(!dfn[i]){
            tarjan(i,-1);
        }
    }

    vector<int> bel(n + 1);
    vector<vector<int>> ans;
    int cnt = 0;

    function<void(int)> dfs;
    dfs = [&](int u){
        bel[u] = cnt;
        ans.back().push_back(u);

        for(auto [v,id] : adj[u]){
            if(bridge[id])continue;
            if(bel[v])continue;

            dfs(v);
        }
    };

    for(int i = 1;i <= n;i++){
        if(bel[i])continue;

        cnt++;
        ans.push_back({});
        dfs(i);
    }

    cout << cnt << endl;

    for(auto &cur : ans){
        cout << cur.size() << " ";

        for(auto x : cur){
            cout << x << " ";
        }

        cout << endl;
    }
}
