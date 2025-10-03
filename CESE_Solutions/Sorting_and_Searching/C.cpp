#include <bits/stdc++.h>
using namespace std;

int main()
{   
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, x;
    cin >> n >> x;
    vector<int> p(n);

    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }

    sort(p.begin(), p.end());

    int left = 0, right = n - 1;
    int cnt = 0;

    while (left <= right)
    {
        if (p[left] + p[right] <= x)
        {
            left++;
            right--;
            cnt++;
        }
        else
        {
            right--;
            cnt++;
        }
    }

    cout << cnt << endl;
    return 0;
}