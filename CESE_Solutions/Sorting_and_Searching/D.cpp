#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    multiset<int> H;
    for (int i = 0, x; i < n; ++i)
    {
        cin >> x;
        H.insert(x);
    }

    for (int i = 0, t; i < m; ++i)
    {
        cin >> t;
        auto it = H.upper_bound(t);
        if (it == H.begin())
        {
            cout << "-1\n";
        }
        else
        {
            --it;
            cout << *it << '\n';
            H.erase(it);
        }
    }
    return 0;
}
