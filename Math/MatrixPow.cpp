#include<bits/stdc++.h>
using namespace std;

struct Matrix{
    int n;
    vector<vector<int>> a;

    Matrix(int n) : n(n),a(n,vector<int>(n,0)) {}

    inline int add(int x, int y) const { return (x + y) % MOD; }
    inline int mul(int x, int y) const { return (int)(x * y) % MOD; }


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