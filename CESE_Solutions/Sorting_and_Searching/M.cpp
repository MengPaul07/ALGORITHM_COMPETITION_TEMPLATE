#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;

    multiset<int> tt;

    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;

        auto it = tt.upper_bound(k);

        if (it == tt.end())
            tt.insert(k);

        else
        {
            tt.erase(it);
            tt.insert(k);
        }
    }

    cout << tt.size() << endl;

    return 0;
}

// #include <bits/stdc++.h>
// using namespace std;

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);

//     int n;
//     cin >> n;
//     vector<int> v(n);
//     for (int i = 0; i < n; i++)
//     {
//         cin >> v[i];
//     }

//     vector<int> p;

//     for (int i = 0; i < n; i++)
//     {
//         auto it = lower_bound(p.begin(), p.end(), v[i]);
//         if (it == p.end())
//         {
//             p.push_back(v[i]);
//         }
//         else
//             *it = v[i];
//     }
//     cout << p.size();
// }