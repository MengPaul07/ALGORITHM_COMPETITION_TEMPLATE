#include <bits/stdc++.h>
using namespace std;

namespace SegmentTreeAdd
{
    int n;
    vector<int> a, sum, lazy;

    void init(const vector<int> &arr)
    {
        a = arr;
        n = (int)a.size() - 1;
        sum.assign(4 * n + 5, 0);
        lazy.assign(4 * n + 5, 0);
    }

    void pushUp(int i)
    {
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }

    void apply(int i, int addv, int len)
    {
        sum[i] += addv * len;
        lazy[i] += addv;
    }

    void pushDown(int i, int ln, int rn)
    {
        if (lazy[i] == 0)
            return;
        apply(i << 1, lazy[i], ln);
        apply(i << 1 | 1, lazy[i], rn);
        lazy[i] = 0;
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        pushUp(i);
    }

    void add(int ql, int qr, int v, int l, int r, int i)
    {
        if (ql <= l && r <= qr)
        {
            apply(i, v, r - l + 1);
            return;
        }
        int mid = (l + r) >> 1;
        pushDown(i, mid - l + 1, r - mid);
        if (ql <= mid)
            add(ql, qr, v, l, mid, i << 1);
        if (qr > mid)
            add(ql, qr, v, mid + 1, r, i << 1 | 1);
        pushUp(i);
    }

    int query(int ql, int qr, int l, int r, int i)
    {
        if (ql <= l && r <= qr)
            return sum[i];
        int mid = (l + r) >> 1;
        pushDown(i, mid - l + 1, r - mid);
        int ans = 0;
        if (ql <= mid)
            ans += query(ql, qr, l, mid, i << 1);
        if (qr > mid)
            ans += query(ql, qr, mid + 1, r, i << 1 | 1);
        return ans;
    }
}

namespace SegmentTreeMul
{
    int n, mod;
    vector<int> a, sum, lazyAdd, lazyMul;

    void init(const vector<int> &arr, int modValue)
    {
        a = arr;
        n = (int)a.size() - 1;
        mod = modValue;
        sum.assign(4 * n + 5, 0);
        lazyAdd.assign(4 * n + 5, 0);
        lazyMul.assign(4 * n + 5, 1);
    }

    void pushUp(int i)
    {
        sum[i] = (sum[i << 1] + sum[i << 1 | 1]) % mod;
    }

    void apply(int i, int addv, int mulv, int len)
    {
        sum[i] = (sum[i] * mulv + addv * len) % mod;
        lazyMul[i] = lazyMul[i] * mulv % mod;
        lazyAdd[i] = (lazyAdd[i] * mulv + addv) % mod;
    }

    void pushDown(int i, int ln, int rn)
    {
        if (lazyAdd[i] == 0 && lazyMul[i] == 1)
            return;
        apply(i << 1, lazyAdd[i], lazyMul[i], ln);
        apply(i << 1 | 1, lazyAdd[i], lazyMul[i], rn);
        lazyAdd[i] = 0;
        lazyMul[i] = 1;
    }

    void build(int l, int r, int i)
    {
        if (l == r)
        {
            sum[i] = a[l] % mod;
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        pushUp(i);
    }

    void add(int ql, int qr, int v, int l, int r, int i)
    {
        if (ql <= l && r <= qr)
        {
            apply(i, v, 1, r - l + 1);
            return;
        }
        int mid = (l + r) >> 1;
        pushDown(i, mid - l + 1, r - mid);
        if (ql <= mid)
            add(ql, qr, v, l, mid, i << 1);
        if (qr > mid)
            add(ql, qr, v, mid + 1, r, i << 1 | 1);
        pushUp(i);
    }

    void mul(int ql, int qr, int v, int l, int r, int i)
    {
        if (ql <= l && r <= qr)
        {
            apply(i, 0, v, r - l + 1);
            return;
        }
        int mid = (l + r) >> 1;
        pushDown(i, mid - l + 1, r - mid);
        if (ql <= mid)
            mul(ql, qr, v, l, mid, i << 1);
        if (qr > mid)
            mul(ql, qr, v, mid + 1, r, i << 1 | 1);
        pushUp(i);
    }

    int query(int ql, int qr, int l, int r, int i)
    {
        if (ql <= l && r <= qr)
            return sum[i] % mod;
        int mid = (l + r) >> 1;
        pushDown(i, mid - l + 1, r - mid);
        int ans = 0;
        if (ql <= mid)
            ans = (ans + query(ql, qr, l, mid, i << 1)) % mod;
        if (qr > mid)
            ans = (ans + query(ql, qr, mid + 1, r, i << 1 | 1)) % mod;
        return ans;
    }
}

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
    int n = sz(a) - 1;
    size_ = 1;
    while(size_ < n) size_ <<= 1;

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
    int ans = -INF;
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