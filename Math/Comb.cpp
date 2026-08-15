#include<bits/stdc++.h>
using namespace std;

// 快速逆元：要求 mod 为质数，且 a % mod != 0
int inv(int a, int mod = MOD)
{
    return qpow((a % mod + mod) % mod, mod - 2, mod);
}

//逆元递推
void invs(int n, int mod = MOD)
{
    vector<int> inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        inv[i] = (1LL * (mod - mod / i) * inv[mod % i] % mod);
    }
}


// 组合数预处理：C(n, k) = fac[n] * invfac[k] * invfac[n-k] % mod
namespace Comb
{
    vector<int> fac(maxn + 1,1), invfac(maxn + 1);

    for (int i = 1; i <= maxn; i++)
    {
        fac[i] = (1LL * fac[i - 1] * i % mod);
    }

    invfac[maxn] = qpow(fac[maxn], mod - 2, mod);

    for (int i = maxn; i >= 1; i--)
    {
        invfac[i - 1] = (1LL * invfac[i] * i % mod);
    }


    int C(int n, int k)
    {
        if (k < 0 || k > n)
            return 0;

        if (n > maxn)
            return 0;

        return (1LL * fac[n] * invfac[k] % mod * invfac[n - k] % mod);
    }
}

// 卡特兰数



//Lucas
int n, P;
vector<int> fac, invfac;

int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1)
            res = res * a % P;
        a = a * a % P;
        b >>= 1;
    }
    return res;
}

int C(int n, int k) {
    if (k < 0 || k > n)
        return 0;

    return fac[n] * invfac[k] % P * invfac[n - k] % P;
}

int Lucas(int n, int k) {
    if (k > n)
        return 0;

    int res = 1;

    while (n || k) {
        int ni = n % P;
        int ki = k % P;

        if (ki > ni)
            return 0;

        res = res * C(ni, ki) % P;

        n /= P;
        k /= P;
    }

    return res;
}

void solve(){
    cin >> n >> P;
    int lim = min(n,P - 1);

    fac.assign(lim + 1, 1);
    invfac.assign(lim + 1, 1);

    for (int i = 1; i <= lim; i++)
        fac[i] = fac[i - 1] * i % P;

    invfac[lim] = qpow(fac[lim], P - 2);

    for (int i = lim; i >= 1; i--)
        invfac[i - 1] = invfac[i] * i % P;
}

