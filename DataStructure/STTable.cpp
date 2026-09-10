#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200005; const int LOG = 20; int a[N],lg2[N]; int stMax[N][LOG],stMin[N][LOG];
// 静态区间最值预处理，O(n log n)
// 预处理静态数组的区间最大值和最小值。
void initST(int n){
    lg2[1] = 0;
    for(int i = 2;i <= n;i++)lg2[i] = lg2[i >> 1] + 1;
    for(int i = 1;i <= n;i++)stMax[i][0] = stMin[i][0] = a[i];
    for(int j = 1;j < LOG;j++)
        for(int i = 1;i + (1LL << j) - 1 <= n;i++){
            stMax[i][j] = max(stMax[i][j - 1],stMax[i + (1LL << (j - 1))][j - 1]);
            stMin[i][j] = min(stMin[i][j - 1],stMin[i + (1LL << (j - 1))][j - 1]);
        }
}
// 查询闭区间 [l,r] 的最大值。
int queryMax(int l, int r){
    int k = lg2[r - l + 1];
    return max(stMax[l][k],stMax[r - (1LL << k) + 1][k]);
}
// 查询闭区间 [l,r] 的最小值。
int queryMin(int l, int r){
    int k = lg2[r - l + 1];
    return min(stMin[l][k],stMin[r - (1LL << k) + 1][k]);
}
