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

    // qpow：竞赛里常用写法
    int qpow(int base, int exp, int mod = MOD)
    {
        return power(base, exp, mod);
    }

    // 快速逆元：要求 mod 为质数，且 a % mod != 0
    int inv(int a, int mod = MOD)
    {
        return qpow((a % mod + mod) % mod, mod - 2, mod);
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

    // 组合数预处理：C(n, k) = fac[n] * invfac[k] * invfac[n-k] % mod
    namespace Comb
    {
        vector<int> fac, invfac;
        int max_n = 0;
        int mod = MOD;

        void init(int n, int m = MOD)
        {
            max_n = n;
            mod = m;
            fac.assign(max_n + 1, 1);
            invfac.assign(max_n + 1, 1);

            for (int i = 1; i <= max_n; i++)
            {
                fac[i] = (int)(1LL * fac[i - 1] * i % mod);
            }
            invfac[max_n] = qpow(fac[max_n], mod - 2, mod);
            for (int i = max_n; i >= 1; i--)
            {
                invfac[i - 1] = (int)(1LL * invfac[i] * i % mod);
            }
        }

        int C(int n, int k)
        {
            if (k < 0 || k > n)
                return 0;
            if (n > max_n)
                return 0;
            return (int)(1LL * fac[n] * invfac[k] % mod * invfac[n - k] % mod);
        }
    }
}



