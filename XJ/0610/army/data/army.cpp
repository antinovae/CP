#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2005;
int T,n;
#define ll long long
const ll INF=1e18;
struct point{
    int x,y;
    point operator - (point a){
	return {x-a.x,y-a.y};
    }
    ll operator * (point a){
	return 1ll*x*a.x+y*a.y;
    }
}a[maxn],b[maxn];
ll _dis(point x,point y){
    return (y-x)*(y-x);
}
ll dis(int x,int y){
    return _dis(a[x],b[y]);
}
vector<int>e[maxn];
int g[maxn][maxn],vis[maxn],match[maxn];
void link(int x,int y){
    /* cout<<"link "<<x<<" "<<y<<" "<<dis(x,y)<<endl; */
    g[x][y]=1;
    e[x].push_back(y);
}
int dfs(int x){
    for(auto v:e[x]){
	if(!vis[v]){
	    vis[v]=1;
	    if(!match[v]||dfs(match[v])){
		match[v]=x;
		return 1;
	    }
	}
    }
    return 0;
}
int construct(){
    int ans=0;
    for(int i=1;i<=n;i++){
	memset(vis,0,sizeof(vis));
	if(dfs(i))ans++;
    }
    return ans;
}
int mn[maxn],in[maxn];
vector<int>st;
vector<pair<int,int>>cur,ans;
int bans[maxn],bant[maxn];
void extend(int x){
    /* cout<<"extend "<<x<<endl; */
    /* for(auto v:st)cout<<v<<' ';cout<<endl; */
    if(in[x]){
	/* cout<<"p "<<endl; */
	for(int j=st.size()-1;st[j]!=x;--j){
	    int v=st[j];
	    /* match[mn[v]]=v; */
	    cur.push_back({v,mn[v]});
	}
	/* match[mn[x]]=x; */
	cur.push_back({x,mn[x]});
	return;
    }
    in[x]=1;
    st.push_back(x);
    extend(match[mn[x]]);
    st.pop_back();
    in[x]=0;
}
void init(){
    memset(bans,0,sizeof(bans));
    memset(bant,0,sizeof(bant));
    memset(match,0,sizeof(match));
    memset(g,0,sizeof(g));
    for(int i=1;i<=n;i++){
	e[i].resize(0);
    }
}
int cnt[maxn];
int check(){
    memset(cnt,0,sizeof(cnt));
    for(int i=n+2;i<=2*n+1;i++){
	cnt[match[i]]++;
	if(!match[i]){
	    /* cout<<"lose match "<<i<<endl; */
	    return 0;

	}
	if(cnt[match[i]]>1){
	    /* cout<<"re match "<<i<<" "<<match[i]<<' '<<mn[match[i]]<<endl; */
	    return 0;
	}
    }
    return 1;
}
void _main(){
    init();
    scanf("%lld",&n);
    for(int i=1;i<=n;i++)
	scanf("%lld%lld",&a[i].x,&a[i].y);
    for(int i=n+1;i<=2*n+1;i++)
	scanf("%lld%lld",&b[i].x,&b[i].y);
    for(int i=1;i<=n;i++){
	for(int j=n+2;j<=2*n+1;j++){
	    if(dis(i,j)<=dis(i,n+1))link(i,j);
	}
    }
    if(construct()<n){
	puts("IMPOSSIBLE");
	return;
    }
    vector<int>s,t;
    ans.resize(0);
    while(ans.size()<n){
	s.resize(0),t.resize(0);cur.resize(0);
	for(int i=1;i<=n;i++){
	    if(!bans[i])s.push_back(i);
	}
	for(int i=2+n;i<=2*n+1;i++){
	    if(!bant[i])t.push_back(i);
	}
	for(auto v:t){
	    assert(!bans[match[v]]);
	}
	for(auto x:s){mn[x]=0;}
	for(auto x:s){
	    for(auto v:t){
		if(g[x][v]&&(!mn[x]||dis(x,v)<=dis(x,mn[x]))){
		    mn[x]=v;
		}
	    }
	}
	memset(in,0,sizeof(in));
	/* cout<<"pppp "<<endl; */
	/* for(auto v:s){ */
	/*     cout<<v<<" - "<<mn[v]<<endl; */
	/* } */
	/* for(auto v:t){ */
	/*     cout<<match[v]<<" - "<<v<<endl; */
	/* } */
	/* cout<<endl; */
	extend(s.front());
	assert(check());
	for(auto [u,v]:cur){
	    bans[u]=1;
	    bant[v]=1;
	    /* cout<<"push "<<u<<' '<<v<<endl; */
	    ans.push_back({u,v});
	}
	/* cout<<"fin "<<ans.size()<<endl; */
    }
    puts("POSSIBLE");
    for(auto [u,v]:ans){
	printf("%lld %lld\n",u,v-n);
    }
}
signed main(){
    freopen("army.in","r",stdin);
    freopen("army.out","w",stdout);
    scanf("%lld",&T);
    while(T--){
	_main();
	/* exit(0); */
    }
}
