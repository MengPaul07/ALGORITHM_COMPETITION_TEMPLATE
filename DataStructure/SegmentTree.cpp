#include <bits/stdc++.h>
using namespace std;

const int INF = (1LL << 62);

struct Node{
    int sum = 0;
    int mn = INF;
    int mx = -INF;
};

Node merge(const Node &a,const Node &b){
    Node res;
    res.sum = a.sum + b.sum;
    res.mn = min(a.mn,b.mn);
    res.mx = max(a.mx,b.mx);
    return res;
}

struct SegmentTreeAdd{
    int n = 0;

    vector<int> a;
    vector<Node> tree;

    vector<int> lazyAdd;
    vector<int> lazySet;
    vector<int> hasSet;

    void init(const vector<int> &arr){
        n = (int)arr.size() - 1;
        a = arr;

        tree.assign(4 * n + 5, Node());
        lazyAdd.assign(4 * n + 5, 0);
        lazySet.assign(4 * n + 5, 0);
        hasSet.assign(4 * n + 5, 0);

        if(n)build(1,n,1);
    }

    void build(int l,int r,int p){
        if(l == r){
            tree[p] = {a[l],a[l],a[l]};
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

    void applySet(int p,int v,int len){
        tree[p].sum = v * len;
        tree[p].mn = v;
        tree[p].mx = v;

        lazySet[p] = v;
        hasSet[p] = 1;
        lazyAdd[p] = 0;
    }

    void applyAdd(int p,int v,int len){
        tree[p].sum += v * len;
        tree[p].mn += v;
        tree[p].mx += v;

        lazyAdd[p] += v;
    }

    void pushDown(int p,int ln,int rn){
        if(hasSet[p]){
            applySet(p << 1,lazySet[p],ln);
            applySet(p << 1 | 1,lazySet[p],rn);

            hasSet[p] = 0;
        }

        if(lazyAdd[p]){
            applyAdd(p << 1,lazyAdd[p],ln);
            applyAdd(p << 1 | 1,lazyAdd[p],rn);

            lazyAdd[p] = 0;
        }
    }

    void add(int ql,int qr,int v){
        if(ql > qr || !n)return;
        add(ql,qr,v,1,n,1);
    }

    void add(int ql,int qr,int v,int l,int r,int p){
        if(ql <= l && r <= qr){
            applyAdd(p,v,r - l + 1);
            return;
        }

        int mid = (l + r) >> 1;
        pushDown(p,mid - l + 1,r - mid);

        if(ql <= mid)add(ql,qr,v,l,mid,p << 1);
        if(qr > mid)add(ql,qr,v,mid + 1,r,p << 1 | 1);

        pushUp(p);
    }

    void modify(int ql,int qr,int v){
        if(ql > qr || !n)return;
        modify(ql,qr,v,1,n,1);
    }

    void modify(int ql,int qr,int v,int l,int r,int p){
        if(ql <= l && r <= qr){
            applySet(p,v,r - l + 1);
            return;
        }

        int mid = (l + r) >> 1;
        pushDown(p,mid - l + 1,r - mid);

        if(ql <= mid)modify(ql,qr,v,l,mid,p << 1);
        if(qr > mid)modify(ql,qr,v,mid + 1,r,p << 1 | 1);

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

struct SegmentTreeMul{
    int n = 0;
    int mod = 1;
    vector<int> a,sum,lazyAdd,lazyMul;

    void init(const vector<int> &arr,int modValue){
        n = (int)arr.size() - 1;
        mod = modValue;
        a.assign(n + 1,0);
        for(int i = 1;i <= n;i++)a[i] = arr[i];

        sum.assign(4 * n + 5,0);
        lazyAdd.assign(4 * n + 5,0);
        lazyMul.assign(4 * n + 5,1);
        if(n)build(1,n,1);
    }

    int norm(int x){
        x %= mod;
        if(x < 0)x += mod;
        return x;
    }

    void build(int l,int r,int p){
        if(l == r){
            sum[p] = norm(a[l]);
            return;
        }

        int mid = (l + r) >> 1;
        build(l,mid,p << 1);
        build(mid + 1,r,p << 1 | 1);
        pushUp(p);
    }

    void pushUp(int p){
        sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % mod;
    }

    void apply(int p,int addv,int mulv,int len){
        addv = norm(addv);
        mulv = norm(mulv);

        sum[p] = (sum[p] * mulv + addv * len) % mod;
        lazyMul[p] = lazyMul[p] * mulv % mod;
        lazyAdd[p] = (lazyAdd[p] * mulv + addv) % mod;
    }

    void pushDown(int p,int ln,int rn){
        if(lazyAdd[p] == 0 && lazyMul[p] == 1)return;

        apply(p << 1,lazyAdd[p],lazyMul[p],ln);
        apply(p << 1 | 1,lazyAdd[p],lazyMul[p],rn);
        lazyAdd[p] = 0;
        lazyMul[p] = 1;
    }

    void add(int ql,int qr,int v){
        if(ql > qr || !n)return;
        add(ql,qr,v,1,n,1);
    }

    void add(int ql,int qr,int v,int l,int r,int p){
        if(ql <= l && r <= qr){
            apply(p,v,1,r - l + 1);
            return;
        }

        int mid = (l + r) >> 1;
        pushDown(p,mid - l + 1,r - mid);
        if(ql <= mid)add(ql,qr,v,l,mid,p << 1);
        if(qr > mid)add(ql,qr,v,mid + 1,r,p << 1 | 1);
        pushUp(p);
    }

    void mul(int ql,int qr,int v){
        if(ql > qr || !n)return;
        mul(ql,qr,v,1,n,1);
    }

    void mul(int ql,int qr,int v,int l,int r,int p){
        if(ql <= l && r <= qr){
            apply(p,0,v,r - l + 1);
            return;
        }

        int mid = (l + r) >> 1;
        pushDown(p,mid - l + 1,r - mid);
        if(ql <= mid)mul(ql,qr,v,l,mid,p << 1);
        if(qr > mid)mul(ql,qr,v,mid + 1,r,p << 1 | 1);
        pushUp(p);
    }

    int query(int ql,int qr){
        if(ql > qr || !n)return 0;
        return query(ql,qr,1,n,1);
    }

    int query(int ql,int qr,int l,int r,int p){
        if(ql <= l && r <= qr)return sum[p];

        int mid = (l + r) >> 1;
        pushDown(p,mid - l + 1,r - mid);
        int ans = 0;
        if(ql <= mid)ans = (ans + query(ql,qr,l,mid,p << 1)) % mod;
        if(qr > mid)ans = (ans + query(ql,qr,mid + 1,r,p << 1 | 1)) % mod;
        return ans;
    }
};

namespace DynamicSegmentTree
{
    const int MAXN = 3000000;
    int ls[MAXN], rs[MAXN], sum[MAXN], lazyAdd[MAXN];
    int cnt = 0;

    int newNode()
    {
        return ++cnt;
    }

    void pushUp(int i)
    {
        sum[i] = (ls[i] ? sum[ls[i]] : 0) + (rs[i] ? sum[rs[i]] : 0);
    }

    void apply(int i, int v, int l, int r)
    {
        if (!i)
            return;
        sum[i] += v * (r - l + 1);
        lazyAdd[i] += v;
    }

    void pushDown(int i, int l, int r)
    {
        if (lazyAdd[i] == 0)
            return;
        int mid = (l + r) >> 1;
        if (!ls[i])
            ls[i] = newNode();
        if (!rs[i])
            rs[i] = newNode();
        apply(ls[i], lazyAdd[i], l, mid);
        apply(rs[i], lazyAdd[i], mid + 1, r);
        lazyAdd[i] = 0;
    }

    void add(int ql, int qr, int v, int l, int r, int &i)
    {
        if (!i)
            i = newNode();
        if (ql <= l && r <= qr)
        {
            sum[i] += v * (r - l + 1);
            lazyAdd[i] += v;
            return;
        }
        pushDown(i, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            add(ql, qr, v, l, mid, ls[i]);
        if (qr > mid)
            add(ql, qr, v, mid + 1, r, rs[i]);
        pushUp(i);
    }

    int query(int ql, int qr, int l, int r, int i)
    {
        if (!i)
            return 0;
        if (ql <= l && r <= qr)
            return sum[i];
        pushDown(i, l, r);
        int mid = (l + r) >> 1;
        int ans = 0;
        if (ql <= mid)
            ans += query(ql, qr, l, mid, ls[i]);
        if (qr > mid)
            ans += query(ql, qr, mid + 1, r, rs[i]);
        return ans;
    }
}


// zkw SegmentTree max

const int N = 600005;

int tree[N << 2];
int size_;

void build(vector<int> &a){
    int n = (int)a.size() - 1;
    size_ = 1;
    while(size_ < n) size_ <<= 1;

    for(int i = 0;i < (size_ << 1) + 5;i++)
        tree[i] = numeric_limits<int>::min();

    for(int i = 1;i <= n;i++)
        tree[size_ + i - 1] = a[i];

    for(int i = size_ - 1;i;i--)
        tree[i] = max(tree[i << 1],tree[i << 1 | 1]);
}

void add(int pos,int val){
    pos += size_ - 1;
    tree[pos] += val;

    while(pos >>= 1)
        tree[pos] = max(tree[pos << 1],tree[pos << 1 | 1]);
}

int query(int l,int r)
{
    int ans = numeric_limits<int>::min();
    l += size_ - 1;
    r += size_ - 1;
    while(l <= r)
    {
        if(l & 1)
            ans = max(ans,tree[l++]);
        if(!(r & 1))
            ans = max(ans,tree[r--]);
        l >>= 1;
        r >>= 1;
    }
    return ans;
}

int find(int l,int x,int node,int L,int R){
    if(R < l || tree[node] < x)
        return -1;

    if(L == R)
        return L;

    int mid = (L + R) >> 1;

    int res = find(l,x,node << 1,L,mid);

    if(res != -1)
        return res;

    return find(l,x,node << 1 | 1,mid + 1,R);
}

int find(int l,int x){
    return find(l,x,1,1,size_);
}
