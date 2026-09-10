#include<bits/stdc++.h>
using namespace std;
const int N = 50005; int mu[N], pre[N]; int prime[N], pcnt; bool vis[N];
// 线性筛计算莫比乌斯函数 mu，并预处理其前缀和。
void init(){
    mu[1] = 1;
    for(int i = 2;i < N;i++){
        if(!vis[i]){
            prime[pcnt++] = i;
            mu[i] = -1;
        }
        for(int j = 0;j < pcnt && i * prime[j] < N;j++){
            int x = i * prime[j];
            vis[x] = 1;
            if(i % prime[j] == 0){
                mu[x] = 0;
                break;
            }
            mu[x] = -mu[i];
        }
    }
    //求和
    for(int i = 1;i < N;i++){
        pre[i] = pre[i - 1] + mu[i];
    }
}
// 用整除分块统计 1<=x<=n、1<=y<=m 且 gcd(x,y)=1 的数对数量。
int calc(int n,int m){
    if(n <= 0 || m <= 0)return 0;
    int ans = 0;
    for(int l = 1,r;l <= min(n,m);l = r + 1){
        int qn = n / l; int qm = m / l;
        r = min(n / qn,m / qm);
        ans += (pre[r] - pre[l - 1]) * qn * qm;
    }
    return ans;
}
// 读入若干组 (a,b,d)，统计 gcd(x,y)=d 的对应互质缩放数对。
void solve(){
    init();
    int n;cin >> n;
    for(int i = 1;i <= n;i++){
        int a,b,d;cin >> a >> b >> d;
        //gcd(x,y) = k -> gcd(kx,ky) = 1
        cout << calc(a / d,b / d) << endl;
    }
}
