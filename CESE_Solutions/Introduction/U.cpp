#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (int i = 0; i < n; ++i)
        cin >> g[i];

    vector<string> ans = g;
    bool vis[505][505];
    memset(vis, 0, sizeof(vis));
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            bool ban[4] = {false};
            ban[g[i][j] - 'A'] = true; 
            for (int d = 0; d < 4; ++d)
            {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m||!vis[ni][nj])
                    continue;
                char c = ans[ni][nj]; 
                ban[c - 'A'] = true;
            }
            char pick = 0;
            for (char c = 'A'; c <= 'D'; ++c)
            {
                if (c != g[i][j] && !ban[c - 'A'])
                {
                    vis[i][j] = 1;
                    pick = c;
                    break;
                }
            }
            if (!pick)
            {
                cout << "IMPOSSIBLE\n";
                return 0;
            }
            ans[i][j] = pick;
        }
    }

    for (int i = 0; i < n; ++i)
        cout << ans[i] << '\n';
    return 0;
}