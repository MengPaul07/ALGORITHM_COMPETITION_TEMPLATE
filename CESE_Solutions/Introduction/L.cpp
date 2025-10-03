#include <bits/stdc++.h>
using namespace std;

int cnt = 0;
string res;
vector<bool> used;

void dfs(int step, int n, const string &s, bool fs)
{
    if (step == n)
    {
        if (!fs) 
            cout << res << '\n';
        ++cnt; 
        return;
    }
    for (int i = 0; i < n; ++i)
    {
        if (i && s[i] == s[i - 1] && !used[i - 1])
            continue;
        if (!used[i])
        {
            used[i] = true;
            res[step] = s[i];
            dfs(step + 1, n, s, fs);
            used[i] = false;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    sort(s.begin(), s.end());

    int n = s.size();
    used.resize(n, false);
    res.resize(n);

    dfs(0, n, s, true);
    cout << cnt << '\n';

    cnt = 0; 
    dfs(0, n, s, false);

    return 0;
}