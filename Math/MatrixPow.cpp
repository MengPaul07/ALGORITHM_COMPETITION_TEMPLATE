#include <bits/stdc++.h>
using namespace std;
struct Matrix{
    int n;
    vector<vector<int>> a;
    Matrix(int n) : n(n),a(n,vector<int>(n,0)) {}
    // 在模 MOD 下做加法，避免矩阵乘法中重复写取模逻辑。
    inline int add(int x, int y) const { return (x + y) % MOD; }
    // 在模 MOD 下做乘法。
    inline int mul(int x, int y) const { return (int)(x * y) % MOD; }
    // 计算两个同阶矩阵的乘积。
    Matrix operator*(const Matrix& other) const {
        Matrix res(n);
        for(int i = 0;i < n;i++){
            for(int k = 0; k < n;k++){
                if(a[i][k]){
                    for(int j = 0;j < n;j++){
                        res.a[i][j] = add(res.a[i][j], mul(a[i][k], other.a[k][j]));
                    }
                }
            }
        }
        return res;
    }
    // 二进制快速幂计算当前矩阵的 k 次幂。
    Matrix pow(int k) const {
        Matrix res(n),base = *this;
        for(int i = 0;i < n;i++)res.a[i][i] = 1;
        while(k){
            if(k & 1) res = res * base;
            base = base * base;
            k >>= 1;
        }
        return res;
    }
};
// 示例：用矩阵快速幂计算第 n 个 Fibonacci 数。
void solve(){
    int n;cin >> n; Matrix base(2);
    base.a[0][0] = 1;
    base.a[0][1] = 1;
    base.a[1][0] = 1;
    base.a[1][1] = 0;
    Matrix ans = base.pow(n);
    cout << ans.a[0][1] << endl;
}
