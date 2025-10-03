#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

        int n;

        cin >> n;

        for (int i = 1; i <= n;i++){
            cout << (i * i  * (i * i - 1))/2 -(4 * (i - 1) * (i - 2)) << endl;
        }

            return 0;
}