#include <bits/stdc++.h>
using namespace std;
// 用 Booth 思想求字典序最小循环表示，并输出该旋转。
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
