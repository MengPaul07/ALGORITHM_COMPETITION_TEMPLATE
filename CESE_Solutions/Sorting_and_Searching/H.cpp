#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    vector<int> diff(n); 

    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    sort(v.begin(),v.end());

    int ave = v[n / 2];
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += llabs(v[i] - ave);
    }
    cout << sum;
    return 0;
}