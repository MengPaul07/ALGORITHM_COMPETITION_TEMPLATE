#include <bits/stdc++.h>
using namespace std;

void solve(){
    string s;
    cin >> s;

    int n = s.length();
    vector<int> d1(n + 1),d2(n + 1);

    int l = 0,r = -1;
    for(int i = 0;i < n;i++){
        if(i > r)d1[i] = 1;
        else d1[i] = min(d1[r + l - i],r - i + 1);

        while(i - d1[i] >= 0 && i + d1[i] < n && s[i - d1[i]] == s[i + d1[i]]){
            d1[i]++;
        }

        if(i + d1[i] - 1 > r){
            l = i - d1[i] + 1;
            r = i + d1[i] - 1;
        }
    }

    l = 0,r = -1;
    for(int i = 0;i < n;i++){
        if(i > r)d2[i] = 0;
        else d2[i] = min(d2[r + l - i + 1],r - i + 1);

        while(i - d2[i] - 1 >= 0 && i + d2[i] < n && s[i - d2[i] - 1] == s[i + d2[i]]){
            d2[i]++;
        }

        if(i + d2[i] - 1 > r){
            l = i - d2[i];
            r = i + d2[i] - 1;
        }
    }


    int ans = 0;
    for(int i = 0;i < n;i++){
        ans = max({ans,2 * d1[i] - 1,2 * d2[i]});
    }

    cout << ans << endl;

}

