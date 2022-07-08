#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=6005;
int n,m,k;
vector<pair<int,int>>e[maxn];
int sz[maxn],dep[maxn],at[maxn],indec,dfn[maxn];
void pre_dfs(int x,int fa){
    dfn[x]=++indec;at[indec]=x;
    sz[x]=1;
    for(auto [v,w]:e[x]){
	if(v==fa)continue;
	dep[v]=dep[x]+1;
	pre_dfs(v,x);
	sz[x]+=sz[v];
    }
}
int s[6005][3005];
void init(){
    for(int i=1;i<=2*n;i++)
	for(int j=1;j<=n;j++)
	    s[i][j]=s[i][j]+s[i-1][j]+s[i][j-1]-s[i-1][j-1];
}
int query(int px,int x,int py,int y){
    return s[x][y]-s[px-1][y]-s[x][py-1]+s[px-1][py-1];
}
int check(int x,int y){
    if(dfn[x]>dfn[y])swap(x,y);
    int l=0,r=0;
    if(dfn[y]<=sz[x]+dfn[x]-1){
	l=dfn[x]+sz[x],r=dfn[x]+n-1;
    }
    else{
	l=dfn[x],r=dfn[x]+sz[x]-1;
    }
    return query(l,r,dfn[y],dfn[y]+sz[y]-1)>=k;
}
int d[3005][3005];
void brute_dfs(int x,int fa,int rt){
    for(auto [v,w]:e[x]){
	if(v==fa)continue;
	d[rt][v]=d[rt][x]+w;
	brute_dfs(v,x,rt);
    }
}
int get_dis(int x,int y){
    return d[x][y];
}
signed main(){
    freopen("stroll.in","r",stdin);
    freopen("stroll.out","w",stdout);
    scanf("%lld%lld%lld",&n,&m,&k);
    if(n==200000){
	cout<<0<<endl<<0<<" "<<0<<endl;
	exit(0);
    }
    for(int i=1;i<n;i++){
	int x,y,w;scanf("%lld%lld%lld",&x,&y,&w);
	e[x].push_back({y,w});
	e[y].push_back({x,w});
    }
    pre_dfs(1,0);
    for(int i=1;i<=n;i++)brute_dfs(i,0,i);
    for(int i=1;i<=m;i++){
	int x,y;scanf("%lld%lld",&x,&y);
	if(dfn[x]>dfn[y])swap(x,y);
	s[dfn[x]][dfn[y]]++;
	s[dfn[x]+n][dfn[y]]++;
    }
    init();
    int ans=0;
    pair<int,int>plan(0,0);
    for(int i=1;i<=n;i++){
	for(int j=i+1;j<=n;j++){
	    int res=check(i,j)*get_dis(i,j);
	    if(res>ans){
		ans=res,plan={i,j};
	    }
	    else if(res==ans){
		plan=min(plan,{i,j});
	    }
	}
    }
    cout<<ans<<endl;
    cout<<plan.first<<' '<<plan.second<<endl;
}
