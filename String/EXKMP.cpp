#include<bits/stdc++.h>
using namespace std;

vector<int> get_z(string s){
    int n = sz(s);
    vector<int> z(n);

    z[0] = n;
    int l = 0,r = 0;

    for(int i = 1;i < n;i++){
        if(i < r){
            z[i] = min(r - i,z[i - l]);
        }

        while(i + z[i] < n && s[z[i]] == s[i + z[i]]){
            z[i]++;
        }

        if(i + z[i] > r){
            l = i;
            r = i + z[i];
        }
    }
    return z;
}


void solve(){
    string a,b;cin >> a >> b;
    int m = sz(b);
    int n = sz(a);
    vector<int> z = get_z(b);
    int ans = 0;
    for(int i = 0;i < m;i++){
        ans ^= (i + 1) * (z[i] + 1);
    }
    cout << ans << endl;
    

    vector<int> t(n);
    int l = 0,r = 0;

    for(int i = 0;i < n;i++){
        if(i < r){
            t[i] = min(r - i,z[i - l]);
        }

        while(i + t[i] < n && t[i] < m && b[t[i]] == a[i + t[i]]){
            t[i]++;
        }

        if(i + t[i] > r){
            l = i;
            r = i + t[i];
        }
    }
    
    ans = 0;
    for(int i = 0;i < n;i++){
        ans ^= (i + 1) * (t[i] + 1);
    }
    cout << ans << endl;

}