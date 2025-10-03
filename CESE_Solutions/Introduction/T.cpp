#include <bits/stdc++.h>
using namespace std;

int vis[7][7];
const int dx[] = {1, -1, 0, 0}; // D U L R
const int dy[] = {0, 0, -1, 1};
const char ds[] = "DULR";
string s;
long long cnt = 0;

void dfs(int x, int y, int k)
{

    int minSteps = abs(6 - x) + abs(0 - y);
    if (k + minSteps > 48)
        return;

    if (k == 48){
        cnt += (x == 6 && y == 0);
        return;
    }

    if (x == 6 && y == 0 && k != 48)
        return;

    for (int i = 0; i < x; i++)
        if (y == 6 && vis[i][6] == 0)
            return;

    for (int i = y; i < 7; i++)
        if (x == 6 && vis[6][i] == 0)
            return;

    for (int i = 0; i < x; i++)
        if (y == 0 && vis[i][0] == 0)
            return;

    for (int i = 0; i < y; i++)
        if (x == 0 && vis[0][i] == 0)
            return;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= 7 || ny >= 7 || vis[nx][ny])
            continue;
        char c = ds[i];
        if (s[k] != '?' && s[k] != c)
            continue;
        vis[nx][ny] = 1;
        dfs(nx, ny, k + 1);
        vis[nx][ny] = 0;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    vis[0][0] = 1;
    dfs(0, 0, 0);
    cout << cnt << '\n';
}