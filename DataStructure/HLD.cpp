#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()

const int INF = (1LL << 62);
const int MOD = 1e9 + 7;
const int mod = 998244353;

int M;

struct Node{
    int sum = 0;
    int mn = INF;
    int mx = -INF;
};

Node merge(Node a,Node b){
    Node res;
    res.sum = (a.sum + b.sum) % M;
    res.mn = min(a.mn,b.mn);
    res.mx = max(a.mx,b.mx);
    return res;
}

struct SegmentTreeAdd{
    int n = 0;
    vector<Node> tree;
    vector<int> lazy;
    vector<int> a;

    void init(const vector<int> &arr){
        n = (int)arr.size() - 1;
        a.assign(n + 1, 0);
        for(int i = 1;i <= n;i++)a[i] = arr[i];
        tree.assign(4 * n + 5, Node());
        lazy.assign(4 * n + 5, 0);
        if(n)build(1,n,1);
    }

    void build(int l,int r,int p){
        if(l == r){
            tree[p] = {a[l] % M,a[l],a[l]};
            return;
        }
        int mid = (l + r) >> 1;
        build(l,mid,p << 1);
        build(mid + 1,r,p << 1 | 1);
        pushUp(p);
    }

    void pushUp(int p){
        tree[p] = merge(tree[p << 1],tree[p << 1 | 1]);
    }

    void apply(int p,int v,int len){
        tree[p].sum += v * len;
        tree[p].sum %= M;
        tree[p].mn += v;
        tree[p].mx += v;
        lazy[p] += v;
        lazy[p] %= M;
    }

    void pushDown(int p,int ln,int rn){
        if(lazy[p] == 0)return;
        apply(p << 1,lazy[p],ln);
        apply(p << 1 | 1,lazy[p],rn);
        lazy[p] = 0;
    }

    void add(int ql,int qr,int v){
        if(ql > qr || !n)return;
        add(ql,qr,v,1,n,1);
    }

    void add(int ql,int qr,int v,int l,int r,int p){
        if(ql <= l && r <= qr){
            apply(p,v,r - l + 1);
            return;
        }
        int mid = (l + r) >> 1;
        pushDown(p,mid - l + 1,r - mid);
        if(ql <= mid)add(ql,qr,v,l,mid,p << 1);
        if(qr > mid)add(ql,qr,v,mid + 1,r,p << 1 | 1);
        pushUp(p);
    }

    Node query(int ql,int qr){
        if(ql > qr || !n)return Node();
        return query(ql,qr,1,n,1);
    }

    Node query(int ql,int qr,int l,int r,int p){
        if(ql <= l && r <= qr)return tree[p];
        int mid = (l + r) >> 1;
        pushDown(p,mid - l + 1,r - mid);
        if(qr <= mid)return query(ql,qr,l,mid,p << 1);
        if(ql > mid)return query(ql,qr,mid + 1,r,p << 1 | 1);
        return merge(
            query(ql,qr,l,mid,p << 1),
            query(ql,qr,mid + 1,r,p << 1 | 1)
        );
    }
};

void solve(){
    int n,m,r,p;cin >> n >> m >> r >> M;
    vector<int> val(n + 1);
    vector<vector<int>> adj(n + 1);
    for(int i = 1;i <= n;i++)cin >> val[i];
    for(int i = 0;i < n - 1;i++){
        int u,v;cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> fa(n + 1),dfn(n + 1),son(n + 1),top(n + 1),
                siz(n + 1,1),dep(n + 1),rev(n + 1);

    function<void(int,int)> dfs1,dfs2;
    dfs1 = [&](int u,int p){
        int mx = 0;
        for(auto v : adj[u]){
            if(v == p)continue;
            fa[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v,u);
            siz[u] += siz[v];
            if(siz[v] > mx){
                son[u] = v; 
                mx = max(mx,siz[v]);
            }
        }
    };

    int timer = 0;
    dfs2 = [&](int u,int tp){
        top[u] = tp;
        dfn[u] = ++timer;
        rev[timer] = u;

        if(son[u] != 0){
            dfs2(son[u],tp);
        }

        for(auto v : adj[u]){
            if(v == fa[u] || v == son[u])continue;
            dfs2(v,v);
        }
    };

    dfs1(r,0);dfs2(r,r);

    vector<int> base(n + 1);

    for(int i = 1;i <= n;i++){
        base[dfn[i]] = val[i];
    }

    SegmentTreeAdd seg;
    seg.init(base);

    function<void(int,int,int)> tadd;
    tadd = [&](int x,int y,int z){
        while(top[x] != top[y]){
            if(dep[top[x]] < dep[top[y]]){
                swap(x,y);
            }
            seg.add(dfn[top[x]],dfn[x],z);

            x = fa[top[x]];
        }

        if(dep[x] > dep[y]){
            swap(x,y);
        }
        seg.add(dfn[x],dfn[y],z);
    };

    function<int(int,int)> tquery;
    tquery = [&](int x,int y){
        int ans = 0;
        while(top[x] != top[y]){
            if(dep[top[x]] < dep[top[y]]){
                swap(x,y);
            }
            ans += seg.query(dfn[top[x]],dfn[x]).sum;
            x = fa[top[x]];
        }

        if(dep[x] > dep[y]){
            swap(x,y);
        }
        ans += seg.query(dfn[x],dfn[y]).sum;
        return ans;
    };

    for(int i = 0;i < m;i++){
        int t;cin >> t;
        if(t == 1){
            int x,y,z;cin >> x >> y >> z;
            tadd(x,y,z);
        }
        if(t == 2){
            int x,y;cin >> x >> y;
            cout << tquery(x,y) % M << endl;
        }
        if(t == 3){
            int x,z;cin >> x >> z;
            int l = dfn[x],r = dfn[x] + siz[x] - 1;
            seg.add(l,r,z);
        }
        if(t == 4){
            int x;cin >> x;
            int l = dfn[x],r = dfn[x] + siz[x] - 1;
            cout << seg.query(l,r).sum % M << endl;
        }
    }
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