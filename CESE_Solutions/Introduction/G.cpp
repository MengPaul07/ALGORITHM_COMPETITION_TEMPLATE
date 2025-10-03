#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long sum0; 
    int n;
    int cnt = 0;

    cin >> n;
    vector<int> v(n + 1, 0); 

    long long total = (long long)n * (n + 1) / 2;
    if (total % 2 != 0)
    {
        cout << "NO";
        return 0;
    }
    else
        cout << "YES" << endl;

    sum0 = (long long)n * (n + 1) / 4; 
    long long ts = 0;                  

    for (int i = n; i > 0; i--)
    {
        if (ts + i <= sum0)
        {
            ts += i;
            cnt++;
            v[i] = 1;
        }
        if (ts == sum0)
            break;
    }

    cout << cnt << endl;
    for (int i = 1; i <= n; i++)
    {
        if (v[i] == 1)
            cout << i << " ";
    }
    cout << endl;

    cout << n - cnt << endl;
    for (int i = 1; i <= n; i++)
    {
        if (v[i] == 0)
            cout << i << " ";
    }

    return 0;
}