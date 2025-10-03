#include <bits/stdc++.h>
using namespace std;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    set<int> s;
    int n;
    cin>>n;
    for (int i = 0; i < n;i++){
        int tmp;
        cin>>tmp;
        s.insert(tmp);
    }
    cout << s.size()<<endl;

        return 0;
}