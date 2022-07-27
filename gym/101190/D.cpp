#include<bits/stdc++.h>
#define LL long long
const int N=1007,M=3*N*2;
const LL INF=0x3f3f3f3f3f3f3f3f;
int S,T,A[N],B[N],Enum,H[N],nxt[M],to[M],cap[M],len[M],cur[N];
bool vis[N];
LL Cost,dis[N];
inline void AE(int u,int v,int w,int c){
    to[++Enum]=v, nxt[Enum]=H[u], H[u]=Enum, cap[Enum]=w, len[Enum]=c;
    to[++Enum]=u, nxt[Enum]=H[v], H[v]=Enum, cap[Enum]=0, len[Enum]=-c;
}
bool SPFA()
{
    static bool inq[N];
    static std::queue<int> q;
    memset(dis,0x3f,(T+1)<<3);
    dis[S]=0, q.push(S);
    while(!q.empty())
    {
        int x=q.front();
        q.pop(), inq[x]=0;
        for(int i=H[x],v; i; i=nxt[i])
            if(cap[i]&&dis[to[i]]>dis[x]+len[i])
                dis[v=to[i]]=dis[x]+len[i], !inq[v]&&(q.push(v),inq[v]=1);
    }
    return dis[T]<INF;
}
bool DFS(int x)
{
    if(x==T) return 1;
    vis[x]=1;
    for(int &i=cur[x],v; i; i=nxt[i])
        if(!vis[v=to[i]]&&dis[v]==dis[x]+len[i]&&cap[i]&&DFS(v))
            return --cap[i],++cap[i^1],Cost+=len[i],1;
    return 0;
}
void MCMF(){
    while(SPFA()){
        memcpy(cur,H,(T+1)<<2), memset(vis,0,T+1);
        while(DFS(S));
    }
}
int e[N];
int n,K,t1,t2;
int main(){
    freopen("delight.in","r",stdin);
    freopen("delight.out","w",stdout);
    scanf("%d%d%d%d",&n,&K,&t1,&t2);
    int P=n+1;
    Enum=1,S=0,T=n+2;LL ans=0;
    for(int i=1;i<=n;++i)scanf("%d",&A[i]),ans+=A[i];
    for(int i=1;i<=n;++i)scanf("%d",&B[i]);
    AE(S,P,K-t1,0);
    for(int i=1; i<=K;++i)AE(P,i,1,0);
    for(int i=1,tmp=K-t1-t2;i<=n; ++i)AE(i,i+1>n?T:i+1,tmp,0),AE(i,i+K>n?T:i+K,1,A[i]-B[i]), e[i]=Enum;
    MCMF(), printf("%lld\n",ans-Cost);
    for(int i=1; i<=n; ++i) putchar(cap[e[i]]?'E':'S');
    return 0;
}
