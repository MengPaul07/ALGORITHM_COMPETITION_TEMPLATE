#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
const int INF = (1LL << 62); const int MOD = 1e9 + 7; const int mod = 998244353; const int N = 1000005;
string s, p; int nxt[N];
// 计算模式串的前缀函数，nxt[i] 是最长相等真前后缀长度。
void getNext()
{
    int m = sz(p);
    nxt[0] = 0;
    for (int i = 1, j = 0; i < m; i++)
    {
        while (j && p[i] != p[j])
            j = nxt[j - 1];
        if (p[i] == p[j]) j++;
        nxt[i] = j;
    }
}
// 用前缀函数扫描文本，输出模式串在 s 中所有 1-based 匹配起点。
void kmp()
{
    int n = sz(s), m = sz(p);
    for (int i = 0, j = 0; i < n; i++)
    {
        while (j && s[i] != p[j])
            j = nxt[j - 1];
        if (s[i] == p[j]) j++;
        if (j == m)
        {
            cout << i - m + 2 << endl;
            j = nxt[j - 1];
        }
    }
}
// 读入文本和模式串，执行 KMP 匹配并输出前缀函数。
void solve()
{
    cin >> s >> p;
    getNext();
    kmp();
    for (int i = 0; i < sz(p); i++)
        cout << nxt[i] << " ";
    cout << endl;
}
