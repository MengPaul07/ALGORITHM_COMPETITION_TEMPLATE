#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 200005;
const int LOG = 20;

struct Edge{
    int u,v,w;
};

int fa[N];
int val[N];

int find(int x){
    if(fa[x]!=x)
        fa[x]=find(fa[x]);
    return fa[x];
}

vector<int> tree[N];


void solve(){

    int n,m;
    cin>>n>>m;

    vector<Edge> edges(m);

    for(auto &[u,v,w]:edges){
        cin>>u>>v>>w;
    }

    sort(edges.begin(),edges.end(),[](Edge a,Edge b){
        return a.w>b.w;   // 最大生成树
    });

    for(int i=1;i<=2*n;i++)
        fa[i]=i;

    int tot=n;

    for(auto [u,v,w]:edges){
        int fu=find(u);
        int fv=find(v);
        if(fu==fv)continue;
        ++tot;
        val[tot]=w;

        tree[tot].push_back(fu);
        tree[tot].push_back(fv);

        fa[fu]=tot;
        fa[fv]=tot;
        fa[tot]=tot;
    }
    // 找根
    int root=find(1);
}