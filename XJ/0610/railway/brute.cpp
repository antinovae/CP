#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100001;
int tot,n,m,Q,dep[maxn],dis[maxn];
pair<int,int>st[18][maxn<<1],p[maxn<<1];
int lg2[maxn<<1];
void st_init(){
    lg2[1]=0;
    for(int i=2;i<=tot;i++){
	lg2[i]=lg2[i>>1]+1;
    }
    for(int i=1;i<=tot;i++)st[0][i]=p[i];
    for(int j=1;j<=lg2[tot];j++){
	for(int i=1;i<=tot;i++){
	    if(i+(1<<(j-1))<=tot)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	    else st[j][i]=st[j-1][i];
	}
    }
}
int pos[maxn];
int fl;
int get_lca(int x,int y){
    x=pos[x],y=pos[y];
    if(x>y)swap(x,y);
    int len=lg2[y-x+1];
    return min(st[len][x],st[len][y+1-(1<<len)]).second;
}
vector<pair<int,int>>e[maxn];
void dfs(int x,int fa){
    p[++tot]={dep[x],x};
    pos[x]=tot;
    for(auto [v,w]:e[x]){
	if(v==fa)continue;
	dep[v]=dep[x]+1;
	dis[v]=dis[x]+w;
	dfs(v,x);
	p[++tot]={dep[x],x};
    }
}
int get_dis(int x,int y){
    if(x==0||y==0)return 0;
    int z=get_lca(x,y);
    return dis[x]+dis[y]-2*dis[z];
}
struct diam{
    vector<pair<int,int>>bt;
    int l,r;
    void update(int x){
	if(!l&&!r){
	    l=x;
	}
	else{
	    int v1=get_dis(x,r),v2=get_dis(x,l),v=get_dis(l,r);
	    if(v1>=v2&&v1>=v)l=x;
	    if(v2>=v1&&v2>=v)r=x;
	}
    }
    void push(){
	bt.push_back({l,r});
    }
    void pop(){
	if(bt.empty())assert(0);
	l=bt.back().first;
	r=bt.back().second;
	bt.pop_back();
    }
}site[maxn];
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
vector<pair<int,int>>ins_city[maxn<<2];
vector<int>ins_color[maxn<<2];
int col[maxn<<2];
int d[maxn];
int res;
void dfs(int x,int fa,int cur,int bn,int y){
    if(col[x]!=bn&&d[col[x]]){
	res=max(res,cur);
    }
    for(auto [v,w]:e[x]){
	if(v==fa)continue;
	dfs(v,x,cur+w,bn,y);
    }
}
void solve(){
    res=0;
    for(int i=1;i<=n;i++){
	if(!d[col[i]])continue;
	dfs(i,0,0,col[i],i);
    }
    cout<<res<<endl;
}
signed main(){
    scanf("%lld%lld%lld",&n,&m,&Q);
    for(int i=1;i<=n;i++){
	scanf("%lld",&col[i]);
    }
    for(int i=1;i<=m;i++){
	d[i]=1;
    }
    for(int i=1;i<n;i++){
	int x,y,w;
	scanf("%lld%lld%lld",&x,&y,&w);
	e[x].push_back({y,w});
	e[y].push_back({x,w});
    }
    dfs(1,0);
    st_init();
    for(int i=1;i<=Q;i++){
	int opt;
	scanf("%lld",&opt);
	if(opt==1){
	    int u,v;scanf("%lld%lld",&u,&v);
	    col[u]=v;
	}
	else{
	    int x;scanf("%lld",&x);
	    d[x]^=1;
	}
	solve();
    }
}
