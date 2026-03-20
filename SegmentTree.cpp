#include<bits/stdc++.h>
using namespace std;

namespace SegmentTree_add {
    const int N = 1e5 + 5;

    int n;
    vector<int> arr;
    vector<int> sum;
    vector<int> lazy_add;

    void up(int i) {
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }

    void lazy(int i, int v, int len) {
        sum[i] += v * len;
        lazy_add[i] += v;
    }

    void down(int i, int ln, int rn) {
        if (lazy_add[i] != 0) {
            lazy(i << 1, lazy_add[i], ln);
            lazy(i << 1 | 1, lazy_add[i], rn);
            lazy_add[i] = 0;
        }
    }

    void build(int l, int r, int i) {
        if (l == r) {
            sum[i] = arr[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }

    void add(int jobl, int jobr, int jobv, int l, int r, int i) {
        if (jobl <= l && r <= jobr) {
            lazy(i, jobv, r - l + 1);
            return;
        }
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) add(jobl, jobr, jobv, l, mid, i << 1);
        if (jobr > mid) add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        up(i);
    }

    int query(int jobl, int jobr, int l, int r, int i) {
        if (jobl <= l && r <= jobr) {
            return sum[i];
        }

        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);

        int ans = 0;
        if (jobl <= mid) {
            ans += query(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }
}


namespace SegmentTree_mul{
    int mod;
    vector<int> sum, arr, lazy_add, lazy_mul;

    void up(int i) {
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }

    void build(int l, int r, int i) {
        if (l == r) {
            sum[i] = arr[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }

    void lazy(int i,int v1, int v2, int len) {
        sum[i] = (sum[i] * v2 + v1 * len) % mod;
        lazy_mul[i] = (lazy_mul[i] * v2) % mod;
        lazy_add[i] = (lazy_add[i] * v2 + v1) % mod;
    }

    void down(int i, int ln, int rn) {
        if (lazy_add[i] != 0 || lazy_mul[i] != 1) {
            lazy(i << 1, lazy_add[i], lazy_mul[i], ln);
            lazy(i << 1 | 1, lazy_add[i], lazy_mul[i], rn);
            lazy_add[i] = 0;
            lazy_mul[i] = 1;
        }
    }

    void add(int jobl, int jobr, int jobv, int l, int r, int i) {
        if (jobl <= l && r <= jobr) {
            lazy(i, jobv, 1, r - l + 1);
            return;
        }
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) add(jobl, jobr, jobv, l, mid, i << 1);
        if (jobr > mid) add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        up(i);
    }

    void mul(int jobl, int jobr, int jobv, int l, int r, int i) {
        if (jobl <= l && r <= jobr) {
            lazy(i, 0, jobv, r - l + 1);
            return;
        }
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid) mul(jobl, jobr, jobv, l, mid, i << 1);
        if (jobr > mid) mul(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        up(i);
    }

    int query(int jobl, int jobr, int l, int r, int i) {
        if (jobl <= l && r <= jobr) return sum[i];

        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);

        int ans = 0;
        if (jobl <= mid) {
            ans += query(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid) {
            ans += query(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }
}

namespace Dynamic_SegmentTree{
    const int MAXN = 3e6 * 60;
    int ls[MAXN], rs[MAXN], sum[MAXN], lazy_add[MAXN];
    int cnt = 0; 

    int new_node() {
        return ++cnt;
    }

    // 向上更新：求和
    void up(int i) {
        int left_val = ls[i] ? sum[ls[i]] : 0;
        int right_val = rs[i] ? sum[rs[i]] : 0;
        sum[i] = left_val + right_val;
    }

    // 辅助函数：仅负责对已存在的节点打标记
    void apply_lazy(int i, int v, int l, int r) {
        if (!i) return; 
        sum[i] += v * (r - l + 1);
        lazy_add[i] += v;
    }

    // 下传标记：动态开点的核心，下传时才创建子节点
    void down(int i, int l, int r) {
        if (lazy_add[i] == 0) return;
        
        int mid = l + (r - l) / 2;
        if (!ls[i]) ls[i] = new_node();
        if (!rs[i]) rs[i] = new_node();
        
        apply_lazy(ls[i], lazy_add[i], l, mid);
        apply_lazy(rs[i], lazy_add[i], mid + 1, r);
        
        lazy_add[i] = 0; 
    }

    // 区间加法：[jobl, jobr] + jobv
    void add(int jobl, int jobr, int jobv, int l, int r, int &i) {
        if (!i) i = new_node();
        if (jobl <= l && r <= jobr) {
            sum[i] += jobv * (r - l + 1);
            lazy_add[i] += jobv;
            return;
        }
        down(i, l, r);
        int mid = l + (r - l) / 2;
        if (jobl <= mid) {
            add(jobl, jobr, jobv, l, mid, ls[i]);
        }
        if (jobr > mid) {
            add(jobl, jobr, jobv, mid + 1, r, rs[i]);
        }
        up(i);
    }

    int query(int jobl, int jobr, int l, int r, int i) {
        if (!i) return 0; 
        if (jobl <= l && r <= jobr) return sum[i];
        
        down(i, l, r);
        int mid = l + (r - l) / 2;
        int res = 0;
        if (jobl <= mid) res += query(jobl, jobr, l, mid, ls[i]);
        if (jobr > mid) res += query(jobl, jobr, mid + 1, r, rs[i]);
        return res;
    }
}

using namespace SegmentTree_mul;

void solve() {
    int n, m;
    cin >> n >> m >> mod;
    arr.assign(n + 1, 0);
    sum.assign(4 * n + 1, 0);
    lazy_add.assign(4 * n + 1, 0);
    lazy_mul.assign(4 * n + 1, 1);
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    build(1, n, 1);

    for (int i = 0; i < m; i++) {
        int op, l, r, val;
        cin >> op;
        if (op == 2) {
            cin >> l >> r >> val;
            add(l, r, val, 1, n, 1);
        } else if (op == 1) {
            cin >> l >> r >> val;
            mul(l, r, val, 1, n, 1);
        } else {
            cin >> l >> r;
            cout << query(l, r, 1, n, 1) % mod << endl;
        }
    }
}