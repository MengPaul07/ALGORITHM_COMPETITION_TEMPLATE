#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >>n;
    int tmp;
    vector<int> v(n+1, 0);
    for (int i = 1;i<=n;i++){
        cin >> tmp;
        v[tmp]++;
    }
    for (int i = 1; i <= n; i++)
    {
        if(v[i]==0)
            cout << i;
    }

        return 0;
}