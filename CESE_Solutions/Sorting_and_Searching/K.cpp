#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> v1(n + 1), v2(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> v1[i];
        v2[v1[i]] = i;
    }

    
    int cnt = 1;
    for (int i = 2; i <= n; i++)
    {
        if (v2[i] < v2[i - 1])
            cnt++;
    }

    while (m--)
    {
        int a, b; 
        cin >> a >> b;

        if (a == b)
        {
            cout << cnt << "\n";
            continue;
        }

        int val_a = v1[a];
        int val_b = v1[b];

     
        if (v2[val_a] < v2[val_a - 1])
            cnt--;
        if (v2[val_a + 1] < v2[val_a])
            cnt--;

       
        if (val_b != val_a + 1 && v2[val_b] < v2[val_b - 1])
            cnt--;

        if (val_b + 1 != val_a && v2[val_b + 1] < v2[val_b])
            cnt--;


        swap(v1[a], v1[b]);
        
        v2[val_a] = b;
        v2[val_b] = a;

      
        if (v2[val_a] < v2[val_a - 1])
            cnt++;
        if (v2[val_a + 1] < v2[val_a])
            cnt++;

        if ( val_b != val_a + 1 && v2[val_b] < v2[val_b - 1])
            cnt++;
        if (val_b + 1 != val_a && v2[val_b + 1] < v2[val_b])
            cnt++;

        cout << cnt << "\n";
    }
    return 0;
}