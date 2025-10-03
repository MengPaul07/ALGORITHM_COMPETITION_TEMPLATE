#include <bits/stdc++.h>
using namespace std;
#define int long long

const int dx[8] = {-1, -1, 1, 1,2,2,-2,-2};
const int dy[8] = {-2, 2, -2, 2,-1,1,-1,1};

void bfs(int n)
{
    vector<vector<int>> dist(n, vector<int>(n, -1));
    queue<pair<int, int>> q;

    dist[0][0] = 0;
    q.push({0,0});

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];


            if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                dist[nx][ny] == -1)
            {

                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << dist[i][j] << " ";
        cout << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    bfs(n);
    return 0;
}