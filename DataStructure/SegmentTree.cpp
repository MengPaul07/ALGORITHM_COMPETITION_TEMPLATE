#include <bits/stdc++.h>
using namespace std;
const int INF = (1LL << 62);
/*
   这份文件里的线段树按模块复制，不需要整份全抄。
   当前第一个模块 SegmentTreeAdd 支持：区间加、区间赋值、区间和、区间最小值、区间最大值。
   使用它时需要一起复制 Node、merge 和 SegmentTreeAdd。
   如果题目没有区间赋值，只保留区间加：可以删掉 applySet、lazySet、hasSet 和两个 modify 函数。
*/
struct Node{
    int sum = 0;int mn = INF;int mx = -INF;
};
// 合并两个区间的信息，维护区间和、最小值和最大值。
Node merge(const Node &a,const Node &b){
    Node res;
    res.sum = a.sum + b.sum;
    res.mn = min(a.mn,b.mn);
    res.mx = max(a.mx,b.mx);
    return res;
}
// ==================== 模块一：区间加 / 区间赋值 / 区间查询 ====================
// Node 保存一段区间的和、最小值、最大值；lazySet 和 lazyAdd 是两类懒标记。
struct SegmentTreeAdd{
    int n = 0;
    vector<int> a;
    vector<Node> tree;
    vector<int> lazyAdd,lazySet,hasSet;
    // ---------- 初始化与建树：所有用法都需要 ----------
    // 用 1-based 数组初始化支持区间加、区间赋值和区间查询的线段树。
    void init(const vector<int> &arr){
        n = (int)arr.size() - 1;
        a = arr;
        tree.assign(4 * n + 5, Node());
        lazyAdd.assign(4 * n + 5, 0);
        lazySet.assign(4 * n + 5, 0);
        hasSet.assign(4 * n + 5, 0);
        if(n)build(1,n,1);
    }
    // 建立节点 p，覆盖区间 [l,r]。
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
    // ---------- 维护与懒标记：所有区间修改都需要 ----------
    // 根据两个儿子更新节点 p 的区间信息。
    void pushUp(int p){
        tree[p] = merge(tree[p << 1],tree[p << 1 | 1]);
    }
    // 将节点 p 覆盖区间整体赋值为 v，并覆盖已有懒标记。
    void applySet(int p,int v,int len){
        tree[p].sum = v * len;
        tree[p].mn = v;
        tree[p].mx = v;
        lazySet[p] = v;
        hasSet[p] = 1;
        lazyAdd[p] = 0;
    }
    // 将节点 p 覆盖区间整体加 v。
    void applyAdd(int p,int v,int len){
        tree[p].sum += v * len;
        tree[p].mn += v;
        tree[p].mx += v;
        lazyAdd[p] += v;
    }
    // 将赋值标记和加法标记下传给左右儿子。
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
    // ---------- 区间加：需要区间加时复制这一组 ----------
    // 对闭区间 [ql,qr] 整体加 v。
    void add(int ql,int qr,int v){
        if(ql > qr || !n)return;
        add(ql,qr,v,1,n,1);
    }
    // 区间加的递归实现，节点 p 覆盖 [l,r]。
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
    // ---------- 区间赋值：不需要赋值时可以连同 lazySet 一起删掉 ----------
    // 对闭区间 [ql,qr] 整体赋值为 v。
    void modify(int ql,int qr,int v){
        if(ql > qr || !n)return;
        modify(ql,qr,v,1,n,1);
    }
    // 区间赋值的递归实现，节点 p 覆盖 [l,r]。
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
    // ---------- 区间查询：需要查询时复制这一组 ----------
    // 查询闭区间 [ql,qr] 的和、最小值和最大值。
    Node query(int ql,int qr){
        if(ql > qr || !n)return Node();
        return query(ql,qr,1,n,1);
    }
    // 区间查询的递归实现，节点 p 覆盖 [l,r]。
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
// ==================== 模块二：模意义区间加 / 区间乘 / 区间和 ====================
// 与上面的 SegmentTreeAdd 无关，只需要模运算时复制这个结构体即可。
struct SegmentTreeMul{
    int n = 0; int mod = 1;
    vector<int> a,sum,lazyAdd,lazyMul;
    // 初始化支持区间加、区间乘和区间求和的模运算线段树。
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
    // 将 x 规范到 [0,mod) 内。
    int norm(int x){
        x %= mod;
        if(x < 0)x += mod;
        return x;
    }
    // 建立模线段树节点 p，覆盖区间 [l,r]。
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
    // 用两个儿子的模和更新父节点。
    void pushUp(int p){
        sum[p] = (sum[p << 1] + sum[p << 1 | 1]) % mod;
    }
    // 将变换 x -> x*mulv+addv 应用到节点 p。
    void apply(int p,int addv,int mulv,int len){
        addv = norm(addv);
        mulv = norm(mulv);
        sum[p] = (sum[p] * mulv + addv * len) % mod;
        lazyMul[p] = lazyMul[p] * mulv % mod;
        lazyAdd[p] = (lazyAdd[p] * mulv + addv) % mod;
    }
    // 下传区间乘加复合懒标记。
    void pushDown(int p,int ln,int rn){
        if(lazyAdd[p] == 0 && lazyMul[p] == 1)return;
        apply(p << 1,lazyAdd[p],lazyMul[p],ln);
        apply(p << 1 | 1,lazyAdd[p],lazyMul[p],rn);
        lazyAdd[p] = 0;
        lazyMul[p] = 1;
    }
    // 对闭区间 [ql,qr] 整体加 v（模 mod）。
    void add(int ql,int qr,int v){
        if(ql > qr || !n)return;
        add(ql,qr,v,1,n,1);
    }
    // 模线段树区间加的递归实现。
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
    // 对闭区间 [ql,qr] 整体乘 v（模 mod）。
    void mul(int ql,int qr,int v){
        if(ql > qr || !n)return;
        mul(ql,qr,v,1,n,1);
    }
    // 模线段树区间乘的递归实现。
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
    // 查询闭区间 [ql,qr] 的元素和（模 mod）。
    int query(int ql,int qr){
        if(ql > qr || !n)return 0;
        return query(ql,qr,1,n,1);
    }
    // 模线段树区间查询的递归实现。
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
    const int MAXN = 3000000; int ls[MAXN], rs[MAXN], sum[MAXN], lazyAdd[MAXN]; int cnt = 0;
    // 创建一个动态线段树节点并返回其编号。
    int newNode()
    {
        return ++cnt;
    }
    // 根据左右子节点更新动态节点 i 的区间和。
    void pushUp(int i)
    {
        sum[i] = (ls[i] ? sum[ls[i]] : 0) + (rs[i] ? sum[rs[i]] : 0);
    }
    // 将增量 v 应用到动态节点 i 覆盖的区间 [l,r]。
    void apply(int i, int v, int l, int r)
    {
        if (!i) return;
        sum[i] += v * (r - l + 1);
        lazyAdd[i] += v;
    }
    // 创建需要的子节点，并下传动态线段树懒标记。
    void pushDown(int i, int l, int r)
    {
        if (lazyAdd[i] == 0) return;
        int mid = (l + r) >> 1;
        if (!ls[i]) ls[i] = newNode();
        if (!rs[i]) rs[i] = newNode();
        apply(ls[i], lazyAdd[i], l, mid);
        apply(rs[i], lazyAdd[i], mid + 1, r);
        lazyAdd[i] = 0;
    }
    // 动态开点线段树的区间加操作。
    void add(int ql, int qr, int v, int l, int r, int &i)
    {
        if (!i) i = newNode();
        if (ql <= l && r <= qr){
            sum[i] += v * (r - l + 1);
            lazyAdd[i] += v;
            return;
        }
        pushDown(i, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid) add(ql, qr, v, l, mid, ls[i]);
        if (qr > mid) add(ql, qr, v, mid + 1, r, rs[i]);
        pushUp(i);
    }
    // 动态开点线段树的区间和查询。
    int query(int ql, int qr, int l, int r, int i)
    {
        if (!i) return 0;
        if (ql <= l && r <= qr) return sum[i];
        pushDown(i, l, r);
        int mid = (l + r) >> 1; int ans = 0;
        if (ql <= mid) ans += query(ql, qr, l, mid, ls[i]);
        if (qr > mid) ans += query(ql, qr, mid + 1, r, rs[i]);
        return ans;
    }
}
// zkw SegmentTree max
const int N = 600005;
int tree[N << 2]; int siz;
// 建立 ZKW 线段树，维护数组的区间最大值。
void build(vector<int> &a){
    int n = (int)a.size() - 1;
    siz = 1;
    while(siz < n) siz <<= 1;
    for(int i = 0;i < (siz << 1) + 5;i++)
        tree[i] = -INF;
    for(int i = 1;i <= n;i++)
        tree[siz + i - 1] = a[i];
    for(int i = siz - 1;i;i--)
        tree[i] = max(tree[i << 1],tree[i << 1 | 1]);
}
// 将 ZKW 线段树中的单点 pos 增加 val。
void add(int pos,int val){
    pos += siz - 1;
    tree[pos] += val;
    while(pos >>= 1)
        tree[pos] = max(tree[pos << 1],tree[pos << 1 | 1]);
}
// 查询 ZKW 线段树区间 [l,r] 的最大值。
int query(int l,int r)
{
    int ans = -INF;
    l += siz - 1;r += siz - 1;
    while(l <= r)
    {
        if (l & 1) ans = max(ans,tree[l++]);
        if (!(r & 1)) ans = max(ans,tree[r--]);
        l >>= 1;r >>= 1;
    }
    return ans;
}
// 在线段树上寻找下标不小于 l 且值至少为 x 的第一个位置。
int find(int l,int x,int node,int L,int R){
    if (R < l || tree[node] < x) return -1;
    if (L == R) return L;
    int mid = (L + R) >> 1;
    int res = find(l,x,node << 1,L,mid);
    if (res != -1) return res;
    return find(l,x,node << 1 | 1,mid + 1,R);
}
// 查询整个 ZKW 线段树中满足条件的第一个位置。
int find(int l,int x){
    return find(l,x,1,1,siz);
}
