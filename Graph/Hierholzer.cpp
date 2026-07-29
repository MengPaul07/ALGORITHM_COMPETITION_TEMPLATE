    #include <bits/stdc++.h>
    using namespace std;

    #define int long long
    #define endl "\n"
    #define all(x) (x).begin(), (x).end()
    #define rall(x) (x).rbegin(), (x).rend()
    #define sz(x) (int)(x).size()

    // 欧拉路径
    void solve(){
        int n,m;
        cin >> n >> m;
        vector<vector<int>> adj(n + 1);
        vector<int> in(n + 1),out(n + 1);
        for(int i = 0;i < m;i++){
            int u,v;
            cin >> u >> v;
            adj[u].push_back(v);
            in[v]++;
            out[u]++;
        }

        for(int i = 1;i <= n;i++){
            sort(all(adj[i]));
        }

        int start = -1;
        int cnt_start = 0,cnt_end = 0;

        for(int i = 1;i <= n;i++){
            if(in[i] + 1 == out[i]){
                start = i;
                cnt_start++;
            }
            else if(in[i]== out[i] + 1){
                cnt_end++;
            }
            else if(in[i] != out[i]){
                cout << "No" << endl;
                return;
            }
        }

        if(!((cnt_start == 0 && cnt_end == 0) || (cnt_start == 1 && cnt_end == 1))){
            cout << "No" << endl;
            return;
        }

        if(start == -1){
            for(int i = 1;i <= n;i++){
                if(out[i]){
                    start = i;
                    break;
                }
            }
        }

        if(start == -1){
            cout << 1 << endl;
            return;
        }

            vector<int> it(n + 1),path;
            auto dfs = [&](auto dfs,int u) -> void {
                while(it[u] < sz(adj[u])){
                    int v = adj[u][it[u]];
                    it[u]++;
                    dfs(dfs,v);
                }
                path.push_back(u);
            };
            dfs(dfs,start);

            if(sz(path) != m + 1){
                cout << "No" << endl;
                return;
            }

            reverse(all(path));
            for(auto i : path){
                cout << i << " ";
            }
            cout << endl;


    }

    signed main(){
        ios::sync_with_stdio(0); cin.tie(0);
    #ifdef LOCAL
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
        int t = 1;
        // cin >> t;
        while(t--) solve();
        return 0;
    }