#include<bits/stdc++.h>
using namespace std;
// 用单个模数计算字符串的多项式哈希值。
int B = 131,MOD = 1e9 + 7;
auto hash = [&](string s){
    int res = 0;
    for(int i = 0;i < s.length();i++){
        res = ((int)res * B + s[i]) % MOD;
    }
    return res;
};
// 用两个模数计算字符串哈希，降低冲突概率。
int B = 131,MOD1 = 1e9 + 7,MOD2 = 998244353;
auto hash = [&](string s,int MOD){
    int res = 0;
    for(int i = 0;i < s.length();i++){
        res = ((int)res * B + s[i]) % MOD;
    }
    return res;
};
// 比较两个字符串的双模哈希是否不同；不同则可判定字符串不同。
auto cmp = [&](string s,string t) -> bool {
    return hash(s,MOD1) != hash(t,MOD1) || hash(s,MOD2) != hash(t,MOD2);
};
// 预处理前缀哈希和幂数组，用于 O(1) 查询子串哈希。
vector<int> h(m + 1),p(m + 1);
p[0] = 1;
for(int i = 0;i < m;i++){
    h[i + 1] = (h[i] * B + t[i]) % MOD;
    p[i + 1] = p[i] * B % MOD;
}
// 返回半开区间 [l,r) 的子串哈希值。
auto get = [&](int l,int r){ 
    return (h[r] - h[l] * p[r-l] % MOD + MOD) % MOD;
};
