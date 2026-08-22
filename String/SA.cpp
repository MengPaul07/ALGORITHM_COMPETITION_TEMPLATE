#include <bits/stdc++.h>
using namespace std;

void solve(){
    string s;
    cin >> s;

    int n = s.length();
    s = " " + s;

    //sa[i] pos of rank_i   
    //rk[i] rank of pos_i
    vector<int> sa(n + 1);
    vector<int> rk(n + 2);
    vector<int> tmp(n + 2);

    vector<int> id(n + 1);
    vector<int> cnt(max(300LL,n + 5));

    int m = 300;

    // 初始排名：单个字符
    for(int i = 1;i <= n;i++){
        rk[i] = s[i];
        id[i] = i;
    }

    // 初始按字符计数排序
    for(int i = 1;i <= n;i++)
        cnt[rk[i]]++;
    for(int i = 1;i <= m;i++)
        cnt[i] += cnt[i - 1];
    for(int i = n;i >= 1;i--)
        sa[cnt[rk[i]]--] = i;
    for(int w = 1;;w <<= 1){

        int p = 0;

        // 先按第二关键字排序
        // i+w > n 的第二关键字为 0
        for(int i = n - w + 1;i <= n;i++){
            if(i >= 1)
                id[++p] = i;
        }

        // 其余位置的第二关键字是 rk[i+w]
        // sa 已经按 rk 排序，所以 sa[i]-w 就按第二关键字排好了
        for(int i = 1;i <= n;i++){
            if(sa[i] > w){
                id[++p] = sa[i] - w;
            }
        }

        // 按第一关键字 rk[id[i]] 稳定计数排序
        fill(cnt.begin(),cnt.end(),0);

        for(int i = 1;i <= n;i++){
            cnt[rk[id[i]]]++;
        }
        for(int i = 1;i <= m;i++){
            cnt[i] += cnt[i - 1];
        }
        for(int i = n;i >= 1;i--){
            sa[cnt[rk[id[i]]]--] = id[i];
        }

        // 根据二元组重新离散化
        tmp[sa[1]] = 1;
        p = 1;

        for(int i = 2;i <= n;i++){
            int x = sa[i - 1];
            int y = sa[i];

            int x1 = rk[x];
            int x2 = (x + w <= n ? rk[x + w] : 0);

            int y1 = rk[y];
            int y2 = (y + w <= n ? rk[y + w] : 0);

            if(x1 == y1 && x2 == y2){
                tmp[y] = p;
            }
            else{
                tmp[y] = ++p;
            }
        }

        rk = tmp;
        m = p;

        if(p == n)
            break;
    }

    for(int i = 1;i <= n;i++){
        cout << sa[i] << " ";
    }

    cout << endl;
}

// height[i] == LCP(sa[i - 1],sa[i])
vector<int> height(n + 1);

int k = 0;
for(int i = 1;i <= n;i++){
    int r = rk[i];

    if(r == 1){
        k = 0;
        continue;
    }
    int j = sa[r - 1];

    while(i + k <= n && j + k <= n && s[i + k] == s[j + k]){
        k++;
    }
    height[r] = k;
    if(k)
        k--;
}
