#include<bits/stdc++.h>
#include "still.h"
using namespace std;
#define ll long long
stringstream _cout;
#define cout _cout
const int maxn=1e5+5;
vector<int>e[maxn];
int indec;
ll D;
array<int,maxn>at,dep,beg,ed,dfn,fa;
void init(int n){
    D=0;
    indec=0;
    for(int i=1;i<=n;i++)e[i].clear();
}
void dfs(int x,int fa){
    dep[x]=dep[fa]+1;
    ::fa[x]=fa;
    if(dep[x]==D){
	e[x].clear();
	dfn[x]=++indec;
	beg[x]=ed[x]=indec;
	at[indec]=x;
	/* cout<<"is! "<<x<<" "<<dfn[x]<<endl; */
    }
    else{
	beg[x]=indec+1;
	for(auto v:e[x]){
	    if(v==fa)continue;
	    dfs(v,x);
	}
	ed[x]=indec;
    }
    /* cout<<x<<" "<<beg[x]<<" "<<ed[x]<<' '<<indec<<endl; */
}
int goal,n;
int is_anc(int x){
    return dfn[goal]<=ed[x]&&dfn[goal]>=beg[x];
}
int sum[maxn],cnt[maxn],usum[maxn],ucnt[maxn],sdep;
vector<int>s;
void dfs1(int x,int fa){

    if(is_anc(x)){
	s.push_back(x),sdep+=dep[x];
	cnt[x]++;
	for(auto v:e[x]){
	    if(v==fa)continue;
	    if(is_anc(v))break;
	    /* cout<<"in "<<v<<endl; */
	    s.push_back(v),sdep+=dep[v];
	    cnt[v]++;
	}
    }
    for(auto v:e[x]){
	if(v==fa)continue;
	dfs1(v,x);
	sum[x]+=sum[v]+cnt[v];
	cnt[x]+=cnt[v];
    }
}
void dfs2(int x,int fa){
    for(auto v:e[x]){
	if(v==fa)continue;
	usum[v]=sum[x]-sum[v]-cnt[v]+usum[x]+ucnt[x];
	ucnt[v]=cnt[x]-cnt[v]+ucnt[x];
	dfs2(v,x);
    }
}
int check(int mid){
    goal=at[mid];
    sdep=0;
    s.resize(0);
    /* cout<<"check "<<mid<<" "<<goal<<endl; */
    for(int x=1;x<=n;x++)sum[x]=0,cnt[x]=0,usum[x]=0,ucnt[x]=0;
    dfs1(1,0);
    dfs2(1,0);
    /* for(int i=1;i<=n;i++){ */
	/* cout<<i<<" is? "<<is_anc(i)<<" cnt "<<cnt[i]<<" "<<ucnt[i]<<" sum "<<sum[i]<<" "<<usum[i]<<endl; */
    /* } */
    /* for(auto v:s){ */
	/* cout<<v<<' '; */
    /* } */
    /* cout<<endl; */
    int res=query(s.size(),s);
    /* int res=(-q+sdep+s.size()*D)/2; */
    /* cout<<q<<" sdep "<<sdep<<" sd "<<s.size()*D<<" "<<res<<endl; */
    for(int i=1;i<=mid;i++){
	int x=at[i];
	if(res==sum[x]+usum[x]+ucnt[x]){return 1;}
    }
    return 0;
}

int solve(int n,int lim,vector<int>u,vector<int>v){
    ::n=n;
    init(n);
    for(int i=0;i<n-1;i++){
	e[u[i]].push_back(v[i]);
	e[v[i]].push_back(u[i]);
    }
    dep[0]=-1;
    D=query(1,{1});
    dfs(1,0);
    /* for(int i=1;i<=n;i++){ */
	/* cout<<i<<" "<<dfn[i]<<" range "<<beg[i]<<" "<<ed[i]<<endl; */
    /* } */
    int l=1,r=indec,res=-1;
    while(l<=r){
	int mid=(l+r)/2;
	if(check(mid))res=at[mid],r=mid-1;
	else l=mid+1;
    }
    return res;
}
