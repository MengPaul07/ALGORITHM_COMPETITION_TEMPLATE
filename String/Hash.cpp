#include<bits/stdc++.h>
using namespace std;

// 单模数hash
int B = 131,MOD = 1e9 + 7;
auto hash = [&](string s){
    int res = 0;
    for(int i = 0;i < s.length();i++){
        res = ((int)res * B + s[i]) % MOD;
    }
    return res;
};

// 多模数hash
int B = 131,MOD1 = 1e9 + 7,MOD2 = 998244353;
auto hash = [&](string s,int MOD){
    int res = 0;
    for(int i = 0;i < s.length();i++){
        res = ((int)res * B + s[i]) % MOD;
    }
    return res;
};

auto cmp = [&](string s,string t) -> bool {
    return hash(s,MOD1) != hash(t,MOD1) || hash(s,MOD2) != hash(t,MOD2);
};


// substring
vector<int> h(m + 1),p(m + 1);
p[0] = 1;

for(int i = 0;i < m;i++){
    h[i + 1] = (h[i] * B + t[i]) % MOD;
    p[i + 1] = p[i] * B % MOD;
}

auto get = [&](int l,int r){ 
    return (h[r] - h[l] * p[r-l] % MOD + MOD) % MOD;
};