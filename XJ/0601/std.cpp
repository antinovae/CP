#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=100005;
int n;
vector<int>e[maxn];
namespace Brute{
    int pos[maxn];
    vector<int>g[maxn];
    void oper(int x,int fa){
    for(auto v:e[x]){
        if(v==fa)continue;
        for(auto u:g[v]){
        g[x].push_back(u);
        pos[u]=x;
        }
        g[v].resize(0);
        oper(v,x);
    }
    }
    void brute(){
    int Q;scanf("%lld",&Q);
    for(int i=1;i<=n;i++)g[i].push_back(i),pos[i]=i;
    while(Q--){
        int x;scanf("%lld",&x);
        oper(pos[x],0);
        long long ans=0;
        for(int i=1;i<=n;i++)
        ans+=1ll*g[i].size()*(g[i].size()-1)/2;
        printf("%lld\n",ans);
    }
    }
}
namespace Chain{
    int fa[maxn],pre[maxn],nxt[maxn],sz[maxn];
    long long ans;
    int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
    }
    void oper(int rt){
    int x=pre[rt],y=nxt[rt],sx=sz[x],sy=sz[y];
    long long cur=0;
    cur-=sx*(sx-1)/2;cur-=sy*(sy-1)/2;cur-=sz[rt]*(sz[rt]-1)/2;
    if(x){
        fa[x]=rt;sz[rt]+=sz[x];nxt[pre[x]]=rt;pre[rt]=pre[x];
    }
    if(y<=n){
        fa[y]=rt;sz[rt]+=sz[y];pre[nxt[y]]=rt;nxt[rt]=nxt[y];
    }
    cur+=sz[rt]*(sz[rt]-1)/2;
    ans+=cur;
    }
    void dfs(int x,int fa){
    for(auto v:e[x]){
        if(v==fa)continue;
        pre[v]=x;nxt[x]=v;
        dfs(v,x);
    }
    }
    void chain(){
    int Q,fl=0;scanf("%lld",&Q);
    for(int i=1;i<=n;i++){
        if(e[i].size()==1){
        if(!fl)dfs(i,0),fl=1;
        else nxt[i]=n+1;
        }
    }
    for(int i=1;i<=n;i++){
        fa[i]=i;sz[i]=1;
    }
    while(Q--){
        int x;scanf("%lld",&x);
        oper(find(x));
        printf("%lld\n",ans);
    }
    }
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<n;i++){
    int x,y;
    scanf("%lld%lld",&x,&y);
    e[x].push_back(y);
    e[y].push_back(x);
    }
    int cc=0;
    for(int i=1;i<=n;i++)if(e[i].size()==1)cc++;
    if(n<=3000)Brute::brute();
    else if(cc==2)Chain::chain();
}
