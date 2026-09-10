#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200005; const int M = 200005;
int w[N],v[N],c[N],dp[M]; // 1-based
vector<pair<int,int>> group[N];
// 将容量为 0..W 的背包状态清零。
void clearDP(int W){
    fill(dp,dp + W + 1,0);
}
// dp[j] 表示容量不超过 j 的最大价值
// 处理每件物品最多选一次的 0/1 背包。
void zeroOneKnapsack(int n, int W){
    clearDP(W);
    for(int i = 1;i <= n;i++)
        for(int j = W;j >= w[i];j--)
            dp[j] = max(dp[j],dp[j - w[i]] + v[i]);
}
// 处理每件物品可以选任意次的完全背包。
void completeKnapsack(int n, int W){
    clearDP(W);
    for(int i = 1;i <= n;i++)
        for(int j = w[i];j <= W;j++)
            dp[j] = max(dp[j],dp[j - w[i]] + v[i]);
}
// 多重背包，二进制拆分
// 用二进制拆分处理每件物品有数量上限的多重背包。
void multipleKnapsack(int n, int W){
    clearDP(W);
    for(int i = 1;i <= n;i++){
        int rest = c[i];
        for(int k = 1;k <= rest;k <<= 1){
            int nw = k * w[i],nv = k * v[i];
            for(int j = W;j >= nw;j--)
                dp[j] = max(dp[j],dp[j - nw] + nv);
            rest -= k;
        }
        if(rest){
            int nw = rest * w[i],nv = rest * v[i];
            for(int j = W;j >= nw;j--)
                dp[j] = max(dp[j],dp[j - nw] + nv);
        }
    }
}
// 第 i 组放在 group[i] 中，每组最多选一个
// 处理每组最多选一个物品的分组背包。
void groupedKnapsack(int n, int W){
    clearDP(W);
    for(int i = 1;i <= n;i++)
        for(int j = W;j >= 0;j--)
            for(auto [weight,value] : group[i])
                if (j >= weight) dp[j] = max(dp[j],dp[j - weight] + value);
}
