#include<bits/stdc++.h>
using namespace std;
namespace FenwickTree {
    const int N = 200005; int tree[N]; int n;
    // 返回 x 的最低位 1，用于跳转到树状数组的父节点。
    int lowbit(int x) {
        return x & (-x);
    }
    // 单点增加 d，维护一维前缀和。
    void add(int index, int d) {
        for (int i = index; i <= n; i += lowbit(i)) {
            tree[i] += d;
        }
    }
    // 查询一维前缀 [1,index] 的和。
    int ask(int index) {
        int sum = 0;
        for (int i = index; i > 0; i -= lowbit(i)) {
            sum += tree[i];
        }
        return sum;
    }
    // 查询一维闭区间 [left,right] 的和。
    int query(int left, int right) {
        return ask(right) - ask(left - 1);
    }
}
namespace FenwickTree2D {
    // 二维树状数组 (2D Binary Indexed Tree)
    // 支持单点修改和矩形区域查询
    const int N = 505; int tree[N][N]; int n, m;
    // 初始化
    // 初始化二维树状数组的行列范围并清空数据。
    void init(int rows, int cols) {
        n = rows;
        m = cols;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                tree[i][j] = 0;
    }
    // 单点更新：在 (x, y) 位置加上 d
    // 将二维点 (x,y) 增加 d。
    void add(int x, int y, int d) {
        for (int i = x; i <= n; i += lowbit(i)) {
            for (int j = y; j <= m; j += lowbit(j)) {
                tree[i][j] += d;
            }
        }
    }
    // 查询前缀和：[1, 1] 到 (x, y)
    // 查询二维前缀 [1,x] * [1,y] 的和。
    int ask(int x, int y) {
        int sum = 0;
        for (int i = x; i > 0; i -= lowbit(i)) {
            for (int j = y; j > 0; j -= lowbit(j)) {
                sum += tree[i][j];
            }
        }
        return sum;
    }
    // 查询矩形区域和：[x1, y1] 到 [x2, y2]
    // 查询二维闭矩形 [x1,x2] * [y1,y2] 的和。
    int query(int x1, int y1, int x2, int y2) {
        return ask(x2, y2) - ask(x1 - 1, y2) - ask(x2, y1 - 1) + ask(x1 - 1, y1 - 1);
    }
}
// 使用树状数组离线查询第k小的元素
// 需要先对元素进行离散化，更新时在离散化后的索引位置更新，查询时根据树状数组的前缀和来找到第k小的元素位置
namespace FenwickTreeKth {
    const int N = 1e5 + 5; int tree[N];
    // 在线性树状数组中将离散值 index 增加 d。
    void update(int index, int d, int n) {
        for (int i = index; i <= n; i += lowbit(i)) {
            tree[i] += d;
        }
    }
    // 查询第 k 小的元素位置
    // 用树状数组二进制跳跃查找第 k 小值的离散下标。
    int find(int k, int n) {
        int pos = 0;
        for (int i = 1 << 20; i > 0; i >>= 1) {
            int next_pos = pos + i;
            if (next_pos <= n && tree[next_pos] < k) {
                pos = next_pos;
                k -= tree[pos];
            }
        }
        return pos + 1;
    }
    // 示例：读入频次数组并回答若干个第 k 小查询。
    void solve(){
        // 示例用法
        int n; // 离散化后的元素个数
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            update(arr[i], 1, n); // 更新树状数组
        }
        int q; // 查询次数
        cin >> q;
        while (q--) {
            int k;
            cin >> k;
            int pos = find(k, n); // 查询第 k 小的元素位置
            cout << pos << endl; // 输出结果
        }
    }
}
