#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    ll best = -1e9, cur = 0;
    for (int i = 0, x; i < n; ++i)
    {
        cin >> x;
        cur = max<ll>(x, cur + x); 
        best = max(best, cur);
    }
    cout << best << '\n';
    return 0;
}