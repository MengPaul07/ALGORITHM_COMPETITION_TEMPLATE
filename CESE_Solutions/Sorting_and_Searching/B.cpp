#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> v1(n), v2(m);

    for (int i = 0; i < n; i++)
        cin >> v1[i];
    for (int i = 0; i < m; i++)
        cin >> v2[i];

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    int cnt = 0;
    int i = 0, j = 0;

    while (i < n && j < m)
    {
        if (v2[j] - k <= v1[i] && v1[i] <= v2[j] + k)
        {
            cnt++;
            i++;
            j++;
        }
        else if (v1[i] < v2[j] - k)
            i++;
        else
            j++;

    }

    cout << cnt;
    return 0;
}