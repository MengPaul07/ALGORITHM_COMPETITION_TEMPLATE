#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >>s;
    vector<int> v(s.length(), 1);
    
    
    for (int i = 0; i < s.length()-1;i++){
        if(s[i]==s[i+1])
            v[i + 1]=v[i]+1;
    }
    sort(v.begin(), v.end());
    cout << v[s.length()-1];

    return 0;
}