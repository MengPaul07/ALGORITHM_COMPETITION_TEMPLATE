// #include <bits/stdc++.h>
// using namespace std;

// signed main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);

//     int n;
//     cin >> n;
//     vector<int> v(n),dp(n,1);
//     dp[0] = 1;
//     for (int i = 0; i < n;i++){
//         cin >> v[i];
//     }

//     int val = 0;
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < i; j++)
//         {
//             if(v[i]>v[j]){
//                 dp[i] = max(dp[i], dp[j]+1);
//             }
//         }
//     }
//     int dm=0;
//     for (int i = 0; i < n; i++)
//     {
//         dm = max(dm, dp[i]);
//     }

//     cout << dm;
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }

    vector<int> p;

    for (int i = 0; i < n;i++){
        auto it = lower_bound(p.begin(), p.end(), v[i]);
        if(it==p.end()){
            p.push_back(v[i]);
        }
        else
            *it = v[i];
    }
    cout << p.size();
}