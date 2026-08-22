#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl "\n"
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()

const int INF = (1LL << 62);
const int MOD = 1e9 + 7;
const int mod = 998244353;

void solve(){
    int n;cin >> n;
    vector<int> a(2 * n);
    for(int i = 0;i < n;i++){
        cin >> a[i];
        a[i + n] = a[i];
    }

    int i = 0,j = 1,k = 0;

    while(i < n && j < n && k < n){
        if(a[i + k] == a[j + k]){
            k++;
            continue;
        }

        if(a[i + k] > a[j + k]){
            i += k + 1;
            if(i == j)i++;
        }

        else if(a[i + k] < a[j + k]){
            j += k + 1;
            if(i == j)j++;
        }

        k = 0;
    }

    int p = min(i,j);

    for(int i = 0;i < n;i++){
        cout << a[p + i] << " ";
    }cout << endl;
}

signed main(){
    ios::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}