#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200005; int fa[N];
int siz[N],rankValue[N];
// 初始化 1..n 的并查集，每个点初始为独立集合。
void init(int n){
    iota(fa + 1,fa + n + 1,1);
    fill(siz + 1,siz + n + 1,1);
    fill(rankValue + 1,rankValue + n + 1,0);
}
// 查找 x 所在集合的代表，并进行路径压缩。
int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
// 合并 x、y 所在集合；若原本已连通则返回 false。
bool merge(int x, int y){
    x = find(x); y = find(y);
    if(x == y)return false;
    if(rankValue[x] < rankValue[y])swap(x,y);
    fa[y] = x;
    siz[x] += siz[y];
    if(rankValue[x] == rankValue[y])rankValue[x]++;
    return true;
}
// 返回 x 所在连通块的大小。
int getSize(int x){
    return siz[find(x)];
}
