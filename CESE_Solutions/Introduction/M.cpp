#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    int t = accumulate(v.begin(), v.end(), 0LL);
    int m = t;

    for (int i = 0; i < (1 << n); ++i)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
        {
            if (i >> j & 1)
            {
                sum += v[j];
            }
        }
        m = min(m, abs(t - 2 * sum));
    }
    cout << m;
    return 0;
}