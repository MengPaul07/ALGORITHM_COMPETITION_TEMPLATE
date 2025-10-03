// #include <bits/stdc++.h>
// using namespace std;

// vector<string> vs;

// signed main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cout.tie(nullptr);

//     int n;
//     cin >> n;
//     string s;
//     vs.push_back("0");
//     vs.push_back("1");

//     for (int i = 2; i <= n; ++i)
//     {
//         int m = vs.size();
//         for (int j = m - 1; j >= 0; --j)
//             vs.push_back("1" + vs[j]);
//         for (int j = 0; j < m; ++j)
//             vs[j] = "0" + vs[j]; 
//     }

//     for (auto s : vs)
//         cout << s << endl;
//     return 0;
// }
// /*


// 0   0
// 1   1

// 11   3
// 10   2

// 110   6
// 111   7
// 101   5
// 100   4

// 1100
// 1101
// 1111
// 1110

// */

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int len = 1 << n; 
    for (int k = 0; k < len; ++k)
    {
        int val = k ^ (k >> 1);
        for (int b = n - 1; b >= 0; --b)
            cout << ((val >> b) & 1);
        cout << '\n';
    }
    return 0;
}