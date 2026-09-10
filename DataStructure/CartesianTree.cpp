#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200005; int a[N],ls[N],rs[N],stk[N]; int top,root;
// 小根笛卡尔树，ls/rs 为左右儿子，O(n)
// 按数组下标建立小根笛卡尔树，结果保存在 ls、rs 和 root 中。
void buildCartesian(int n){
    fill(ls + 1,ls + n + 1,0);
    fill(rs + 1,rs + n + 1,0);
    top = root = 0;
    for(int i = 1;i <= n;i++){
        int last = 0;
        while(top && a[stk[top]] > a[i])last = stk[top--];
        ls[i] = last;
        if(top)rs[stk[top]] = i;
        else root = i;
        stk[++top] = i;
    }
}
