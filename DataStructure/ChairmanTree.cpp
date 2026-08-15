#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
const int MAXNODE = N * 25;

struct Node {
    int val,lc,rc;
}tree[MAXNODE];

int tot,n,m;
int a[N],roots[N];

int build(int l,int r){
    int root = ++tot;
    if(l == r){
        tree[root].val = a[l];
        return root;
    }
    int mid = (l + r) / 2;
    tree[root].lc = build(l,mid);
    tree[root].rc = build(mid + 1,r);
    return root;
}

int update(int pre,int l,int r,int pos,int val){
    int root = ++tot;
    tree[root] = tree[pre];
    if(l == r){
        tree[root].val = val;
        return root;
    }
    int mid = (l + r) / 2;
    if(pos <= mid){
        tree[root].lc = update(tree[pre].lc,l,mid,pos,val);
    }
    else{
        tree[root].rc = update(tree[pre].rc,mid + 1,r,pos,val);
    }
    return root;
}

int query(int root,int l,int r,int pos){
    if(l == r)return tree[root].val;
    int mid = (l + r) / 2;
    if(pos <= mid) 
        return query(tree[root].lc,l,mid,pos);
    else 
        return query(tree[root].rc,mid + 1,r,pos);
}

void solve(){
    int n,m;
    cin >> n >> m;
    for(int i = 1;i <= n;i++)
        cin >> a[i];
    
    roots[0] = build(1,n);

    for(int i = 1;i <= m;i++){
        int v,t,p,c;
        cin >> v >> t;
        if(t == 1){
            cin >> p >> c;
            roots[i] = update(roots[v],1,n,p,c); 
        }
        else{
            cin >> p;
            cout << query(roots[v],1,n,p) << endl;
            roots[i] = roots[v];
        }
    }

}


// k-th
const int N = 2e5 + 5;

struct Node{
    int l,r;
    int sum;
}tree[N << 5];

int root[N];
int tot;

void insert(int pre,int &now,int l,int r,int pos){
    now = ++tot;
    tree[now] = tree[pre];
    tree[now].sum++;

    if(l == r)
        return;

    int mid = (l + r) >> 1;
    if(pos <= mid)
        insert(tree[pre].l,tree[now].l,l,mid,pos);
    else
        insert(tree[pre].r,tree[now].r,mid + 1,r,pos);
}

int query(int u,int v,int l,int r,int k){
    if(l == r)
        return l;

    int cnt = tree[tree[v].l].sum - tree[tree[u].l].sum;
    int mid = (l + r) >> 1;

    if(k <= cnt)
        return query(tree[u].l,tree[v].l,l,mid,k);
    else
        return query(tree[u].r,tree[v].r,mid + 1,r,k - cnt);
}

void solve(){
    int n,m;
    cin >> n >> m;

    vector<int> a(n + 1);
    vector<int> dis;

    for(int i = 1;i <= n;i++){
        cin >> a[i];
        dis.push_back(a[i]);
    }

    sort(all(dis));
    dis.erase(unique(all(dis)),dis.end());

    auto get = [&](int x){
        return lower_bound(all(dis),x) - dis.begin() + 1;
    };

    int len = sz(dis);

    for(int i = 1;i <= n;i++)
        insert(root[i - 1],root[i],1,len,get(a[i]));

    while(m--){
        int l,r,k;
        cin >> l >> r >> k;

        int pos = query(root[l - 1],root[r],1,len,k);
        cout << dis[pos - 1] << endl;
    }
}
