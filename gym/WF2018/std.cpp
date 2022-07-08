#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>

#define maxn 1000005
#define INF (1ll<<40)
#define MOD 998244353

using namespace std;

inline int getint()
{
    int num=0,flag=1;char c;
    while((c=getchar())<'0'||c>'9')if(c=='-')flag=-1;
    while(c>='0'&&c<='9')num=num*10+c-48,c=getchar();
    return num*flag;
}

int n,m;
priority_queue<long long,vector<long long>,greater<long long> >Q1[maxn],Q2[maxn];
int A1[maxn],A2[maxn];
int fir[maxn],nxt[maxn],to[maxn],len[maxn],cnt;
long long dis[maxn],ans;

inline void newnode(int u,int v,int w)
{to[++cnt]=v,nxt[cnt]=fir[u],fir[u]=cnt,len[cnt]=w;}

inline void merge(int x,int y)
{
    if(Q1[x].size()<Q1[y].size())swap(Q1[x],Q1[y]);
    while(!Q1[y].empty())Q1[x].push(Q1[y].top()),Q1[y].pop();
    if(Q2[x].size()<Q2[y].size())swap(Q2[x],Q2[y]);
    while(!Q2[y].empty())Q2[x].push(Q2[y].top()),Q2[y].pop();
}

inline void dfs(int u,int fa)
{
    while(A1[u]--)Q1[u].push(dis[u]);
    while(A2[u]--)Q2[u].push(dis[u]-INF);
    for(int i=fir[u];i;i=nxt[i])if(to[i]!=fa)
    {
	dis[to[i]]=dis[u]+len[i],dfs(to[i],u);
	merge(u,to[i]);
    }
    while(!Q1[u].empty()&&!Q2[u].empty()&&Q1[u].top()+Q2[u].top()-2*dis[u]<0)
    {
	long long x=Q1[u].top(),y=Q2[u].top();
	ans+=x+y-2*dis[u],Q1[u].pop(),Q2[u].pop();
	Q1[u].push(2*dis[u]-y),Q2[u].push(2*dis[u]-x);
    }
}

int main()
{
    n=getint();
    for(int i=1;i<n;i++)
    {
	int u=getint(),v=getint(),w=getint();
	newnode(u,v,w),newnode(v,u,w);
    }
    for(int i=1;i<=n;i++)
    {
	A1[i]=getint(),A2[i]=getint();
	int tmp=min(A1[i],A2[i]);
	A1[i]-=tmp,A2[i]-=tmp,m+=A2[i];
    }
    dfs(1,0);
    printf("%lld\n",ans+INF*m);
}

