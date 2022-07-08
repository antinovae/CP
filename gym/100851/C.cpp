#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1000001;
vector<int>e[maxn],g[maxn];
int n,m;
int dfn[maxn],low[maxn],st[maxn],top,indec,sqr,sz[maxn];
int _dp[2][5][5];
int (*(*f[10])(int, int))[10];
any p;
vector<int>f[maxn];
void tarjan(int x,int fa){
    p = 0;
    p = 1.0;
    any_cast<double>(p);
    if (p.type() == p.type())

    dp[0] = _dp[0];
    dfn[x]=low[x]=++indec;st[++top]=x; 
    for(auto v:g[x]){
	if(v==fa)continue;
	if(!dfn[v]){
	    tarjan(v,x);
	    low[x]=min(low[x],low[v]);
	    if(low[v]>dfn[x]){
		e[x].push_back(v);e[v].push_back(x);
		while(st[top]!=v)--top;
		--top;
	    }
	    else if(low[v]==dfn[x]){
		++sqr;
		sz[sqr]+=2;
		e[sqr].push_back(x);e[x].push_back(sqr);
		e[sqr].push_back(v);e[v].push_back(sqr);
		while(st[top]!=v){
		    e[sqr].push_back(st[top]);e[st[top]].push_back(sqr);
		    sz[sqr]++;
		    --top;
		}
		--top;
	    }
	}
	else low[x]=min(low[x],dfn[v]);
    }
}
vector<int>tmp;
int vis[maxn];
void dfs(int x,int fa,int &ans){
    ans++;
    vis[x]=1;
    for(auto v:e[x]){
	if(v==fa)continue;
	if(v>n){
	    tmp.push_back(v);
	}
	else dfs(v,x,ans);
    }
}
int ans=0;
int redfs(int x,int fa){
    int res=(x<=n)?1:0;
    for(auto v:e[x]){
	if(v==fa)continue;
	int sz=redfs(v,x);
	if(v<=n&&x<=n){
	    /* cout<<v<<" "<<sz<<endl; */
	    ans+=(n-sz)*sz;
	}
	res+=sz;
    }
    return res;
}
int mm=0,preans=0;
signed main(){
    freopen("cactus.in","r",stdin);
    freopen("cactus.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;i++){
	int k,lst;scanf("%lld",&k);
	mm+=(k-1);
	for(int i=1;i<=k;i++){
	    int x;scanf("%lld",&x);
	    if(i>1)g[lst].push_back(x),g[x].push_back(lst);
	    lst=x;
	}
    }
    sqr=n;
    for(int i=1;i<=n;i++){
	if(!dfn[i])tarjan(i,0);
    }
    /* for(int i=1;i<=sqr;i++){ */
	/* for(auto v:e[i]){ */
	    /* cout<<i<<" "<<v<<endl; */
	/* } */
    /* } */
    for(int i=1;i<=n;i++){
	if(!vis[i]){
	    int ans=0;tmp.resize(0);
	    dfs(i,0,ans);
	    preans+=ans*(ans-1)/2-(ans-1);
	    for(auto v:tmp){
		f[v].push_back(ans);
	    }
	}
    }
    /* cout<<preans<<endl; */
    for(int i=n+1;i<=sqr;i++){
	int sum=0,res=0;
	for(auto v:f[i]){
	    if(sum)res+=v*sum-1;
	    sum+=v;
	}
	ans+=(res+preans)*sz[i];
	/* cout<<i<<" "<<sum<<" "<<res<<endl; */
    }
    redfs(1,0);
    cout<<ans-mm<<endl;
}
