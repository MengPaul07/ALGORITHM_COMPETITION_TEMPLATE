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

