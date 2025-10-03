#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    int l = 0;
    int ans = 0;
    map<int, int> mp;
    for (int r = 0; r <= n; r++)
    {
        ans += (r - l + 1);
    }
    for (int r = 0; r < n; r++)
    {
        mp[v[r]]++;
        while (mp[v[r]] == 2)
        {
            mp[v[l]]--;
            if (mp[v[l]] == 0)
                mp.erase(v[l]);
            // ans--;
            l++;
        }
    }
    cout << ans;
    return 0;
}