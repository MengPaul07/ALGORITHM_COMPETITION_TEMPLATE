#include <bits/stdc++.h>
using namespace std;

const int N = 8;
char board[N][N];
int cnt = 0;

bool isValid(int row, int col, const vector<int> &placed)
{
    if (board[row][col] == '*')
    {
        return false;
    }

    for (int i = 0; i < row; i++)
    {
        if (placed[i] == col)
        {
            return false;
        }
    }

    for (int i = 0; i < row; i++)
    {
        if (placed[i] != -1)
        {
            if (row - i == col - placed[i])
            {
                return false;
            }
            if (row - i == placed[i] - col)
            {
                return false;
            }
        }
    }

    return true;
}

void dfs(int row, vector<int> &placed)
{
    if (row == N)
    {
        cnt++;
        return;
    }

    for (int col = 0; col < N; col++)
    {
        if (isValid(row, col, placed))
        {
            placed[row] = col;
            dfs(row + 1, placed);
            placed[row] = -1; 
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> board[i][j];
        }
    }

    vector<int> placed(N, -1);
    dfs(0, placed);
    cout << cnt << endl;

    return 0;
}