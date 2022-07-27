#include<bits/stdc++.h>
#define ll long long
#define N 100010
using namespace std;
int nxt[N<<1],to[N<<1],w[N<<1],head[N],cnt;
void add(int u,int v,int w0){nxt[++cnt]=head[u];to[cnt]=v;w[cnt]=w0;head[u]=cnt;}
int d1[N],d2[N],d[N];bool vis[N];
void dij(int s,int d[]) {
    memset(d,0x3f,sizeof(d1));
    memset(vis,0,sizeof(vis));
    priority_queue<pair<int,int>>q;
    d[s]=0;q.push({0,s});
    while(!q.empty()) {
        int u=q.top().second;q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int i=head[u];i;i=nxt[i]) {
            int v=to[i];
            if(d[v]>d[u]+w[i]) d[v]=d[u]+w[i],q.push({-d[v],v});
        }
    }
}
int x[N],y[N],z[N];
ll f[N],g[N];
ll calc(int x,int y){return (g[y]-g[x-1])*(y-x);}
int main() {
    int n,b,p,m;scanf("%d%d%d%d",&n,&b,&p,&m);
    for(int i=1;i<=m;i++) scanf("%d%d%d",&x[i],&y[i],&z[i]),add(x[i],y[i],z[i]);
    dij(b+1,d1);
    for(int i=1;i<=n;i++) head[i]=0;cnt=0;
    for(int i=1;i<=m;i++) add(y[i],x[i],z[i]);
    dij(b+1,d2);
    for(int i=1;i<=b;i++) d[i]=d1[i]+d2[i];
    sort(d+1,d+b+1);
    for(int i=1;i<=b;i++) g[i]=g[i-1]+d[i];
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    for(int i=1;i<=p;i++) {
        for(int j=b;j>=1;j--) {
            f[j]=1e18;
            for(int k=1;k<=j/i && k<=j;k++)
                f[j]=min(f[j],f[j-k]+calc(j-k+1,j));
        }
    }
    printf("%lld\n",f[b]);
    return 0;
}
