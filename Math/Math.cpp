#include <bits/stdc++.h>
using namespace std;

namespace Math
{
    // 常用质数模数
    const int MOD = 1000000007;

    int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }

    int lcm(int a, int b)
    {
        return a / gcd(a, b) * b;
    }

    // exgcd
    int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

    // 快速幂 a^b % mod
    int power(int base, int exp, int mod)
    {
        int res = 1;
        base %= mod;
        while (exp > 0)
        {
            if (exp % 2 == 1)
                res = (res * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return res;
    }

    // 快速幂 a^b
    int power(int base, int exp)
    {
        int res = 1;
        while (exp > 0)
        {
            if (exp % 2 == 1)
                res *= base;
            base *= base;
            exp /= 2;
        }
        return res;
    }

    // 埃氏筛
    namespace Eratosthenes
    {
        const int N = 1000001;
        bool is_prime[N];

        void sieve(int n)
        {
            memset(is_prime, true, sizeof(is_prime));
            is_prime[0] = is_prime[1] = false;
            for (int p = 2; p * p <= n; p++)
            {
                if (is_prime[p])
                {
                    for (int i = p * p; i <= n; i += p)
                        is_prime[i] = false;
                }
            }
        }
    }

    // 欧拉筛 (线性筛)
    namespace Euler
    {
        const int N = 1000001;
        int primes[N];
        bool is_prime[N];
        int prime_count = 0;

        void sieve(int n)
        {
            memset(is_prime, true, sizeof(is_prime));
            is_prime[0] = is_prime[1] = false;
            for (int i = 2; i <= n; i++)
            {
                if (is_prime[i])
                {
                    primes[prime_count++] = i;
                }
                for (int j = 0; j < prime_count && i * primes[j] <= n; j++)
                {
                    is_prime[i * primes[j]] = false;
                    if (i % primes[j] == 0)
                    {
                        break;
                    }
                }
            }
        }
    }

    // 欧拉筛 (线性筛) + 欧拉函数
    namespace EulerPhi
    {
        const int N = 1000001;
        int primes[N];
        bool is_prime[N];
        int phi[N]; // phi[i] 存储 i 的欧拉函数值
        int prime_count = 0;

        void sieve(int n)
        {
            memset(is_prime, true, sizeof(is_prime));
            is_prime[0] = is_prime[1] = false;
            phi[1] = 1;
            for (int i = 2; i <= n; i++)
            {
                if (is_prime[i])
                {
                    primes[prime_count++] = i;
                    phi[i] = i - 1;
                }
                for (int j = 0; j < prime_count && i * primes[j] <= n; j++)
                {
                    is_prime[i * primes[j]] = false;
                    if (i % primes[j] == 0)
                    {
                        phi[i * primes[j]] = phi[i] * primes[j];
                        break;
                    }
                    else
                    {
                        phi[i * primes[j]] = phi[i] * (primes[j] - 1);
                    }
                }
            }
        }
    }

    // 单独计算一个数的欧拉函数
    int euler_phi(int n)
    {
        int result = n;
        for (int i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                while (n % i == 0)
                    n /= i;
                result -= result / i;
            }
        }
        if (n > 1)
            result -= result / n;
        return result;
    }

// EX-EULER 
int euler_phi(int n)
{
    int res = n;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            res -= res / i;
        }
    }
    if (n > 1)
        res -= res / n;
    return res;
}

int qpow(int a,int b,int m){
    int ans = 1 % m;
    a %= m;
    while(b){
        if(b & 1){
            ans = ans * a % m;
        }
        a = a * a % m;
        b >>= 1;
    }
    return ans;
}

void solve(){
    int a,m;string b;cin >> a >> m >> b;
    int phi = euler_phi(m);

    auto get = [&](string s,int mod) {
        int res = 0;
        for(char c : s){
            res = (res * 10 + c - '0') % mod;
        }
        return res;
    };
    
    int M = get(b,phi);

    string sp = to_string(phi);

    bool big = 0;
    if(sz(b) != sz(sp)){
        big = sz(b) > sz(sp);
    }
    else{
        big = b >= sp;
    }

    if(big)M += phi;
    
    cout << qpow(a,M,m) << endl;
}



// CRT
using i128 = __int128_t;

int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

void solve(){
    int n;cin >> n;
    vector<int> a(n),b(n);
    int M = 1;
    for(int i = 0;i < n;i++){
        cin >> a[i] >> b[i];
        M *= a[i];
    }

    int ans = 0;
    for(int i = 0;i < n;i++){
        int Mi = M / a[i];
        int x,y;
        exgcd(Mi,a[i],x,y);

        x = (x % a[i] + a[i]) % a[i];

        ans += (i128)b[i] * Mi % M * x % M;
        ans %= M;
    }
    cout << ans << endl;
}

// EXCRT
using i128 = __int128_t;

int exgcd(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

void solve(){
    int n;cin >> n;
    vector<int> a(n),b(n);
    int M = 1;
    for(int i = 0;i < n;i++){
        cin >> a[i] >> b[i];
    }

    int ans = 0;
    for(int i = 0;i < n;i++){
        int x,y;
        int g = exgcd(M,a[i],x,y);
        int d = b[i] - ans;
    
        if(d % g != 0){
            cout << -1 << endl;
            return;
        }

        int mod2 = a[i] / g;

        i128 k = (i128)(d / g) * x % mod2;
        if(k < 0) k+= mod2;

        i128 lcm = (i128)(M / g) * a[i];
        ans = (int)((i128)ans + (i128)M * k) % lcm;
        M = (int)lcm;
    }
    cout << ans << endl;
}