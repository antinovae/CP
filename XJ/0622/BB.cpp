#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int INF=1e6,maxn=7005;
int n,m,kl=1,dep[maxn],cur[maxn],S,T,head[maxn],fi[maxn];
struct line{int f,to,next,data;}q[maxn*14];
void pushline(int f,int t,int d){
    q[++kl].next=head[f];head[f]=kl;q[kl].to=t;q[kl].data=d;
    q[++kl].next=head[t];head[t]=kl;q[kl].to=f;q[kl].data=0;
}
int bfs(int S,int T){
    int l,r;
    memset(dep,0,sizeof(dep));
    fi[l=r=1]=S;
    dep[S]=1;
    while(l<=r){
        int x=fi[l++];
        for(int p=head[x];p;p=q[p].next){
            int v=q[p].to;
            if(q[p].data&&!dep[v])
                dep[v]=dep[x]+1,fi[++r]=v;
        }
    }
    return dep[T];
}
int dfs(int x,int in,int T){
    if(x==T)return in;
    if(!in)return in;
    int out=0;
    for(int p=cur[x];p;p=q[p].next){
        cur[x]=q[p].next;
        int v=q[p].to;
        if(q[p].data&&dep[v]==dep[x]+1){
            int res=dfs(v,min(q[p].data,in),T);
            q[p].data-=res,q[p^1].data+=res;
            in-=res,out+=res;
	    if(!in)return out;
        }
    }
    if(out==0)dep[x]=0;
    return out;
}
int mxflow(int S,int T){
    int ans=0;
    while(bfs(S,T)){
        for(int i=1;i<=n+m+2;i++)cur[i]=head[i];
        ans+=dfs(S,2e9,T);
    }
    return ans;
}
int id[maxn],_x[maxn],_y[maxn];
int main(){
    freopen("rigid.in","r",stdin);
    freopen("rigid.out","w",stdout);
    scanf("%d%d",&n,&m);
    S=n+m+1,T=n+m+2;
    for(int i=1;i<=n;i++)pushline(i,T,2),id[i]=kl-1;
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
	_x[i]=x,_y[i]=y;
        pushline(i+n,x,INF);pushline(i+n,y,INF);
        pushline(S,i+n,1);
    }
    int res=mxflow(S,T);
    for(int i=1;i<=m;i++){
	int x=_x[i],y=_y[i];
        q[id[x]].data=0;q[id[x]^1].data=0;
        q[id[y]].data=0;q[id[y]^1].data=0;
        res-=mxflow(x,S);
        res-=mxflow(y,S);
        res+=mxflow(S,T);
        if(m-res>1){
            puts("No");
	    return 0;
        }
        q[id[x]].data=2;q[id[x]^1].data=2;
        q[id[y]].data=2;q[id[y]^1].data=2;
    }
    puts("Yes");
}
