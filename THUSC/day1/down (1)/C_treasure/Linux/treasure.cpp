#include<bits/stdc++.h>
using namespace std;
#include "treasure.h"
namespace Alices{
    const int maxn=1e6+5;
    vector<pair<int,int>>e[maxn];
    int vis[maxn],cnt[maxn],sz[maxn],dep[maxn],lim,B;
    void dfs(int x,int fa){
	if(fa==-1)dep[x]=1;
	else dep[x]=dep[fa]+1;
	cnt[dep[x]]++;
	vis[x]=1;
	for(auto [v,id]:e[x]){
	    if(vis[v])continue;
	    dfs(v,x);
	}
    }
}
void Alice(const int testid,const int n,const int m,const int x,const int u[],const int v[],bool dir[]){
    using namespace Alices;
    B=sqrt(n);
    for(int i=0;i<m;i++){
	e[u[i]].push_back({v[i],i});
	e[v[i]].push_back({u[i],i});
    }
    dfs(x,-1);
    /* for(int i=0;i<n;i++){ */
	/* cerr<<dep[i]<<" "; */
    /* } */
    /* for(int i=0;i<n;i++){ */
	/* cerr<<cnt[i]<<" "; */
    /* } */
    for(int i=0;i<n;i++){
	cnt[i]+=cnt[i-1];
	if(cnt[i]>B){
	    lim=i;break;
	}
    }
    /* cerr<<B<<" "<<lim<<endl; */
    for(int i=0;i<m;i++){
	if(dep[u[i]]<dep[v[i]]){
	    if(dep[u[i]]<lim)dir[i]=1;
	    else {
		dir[i]=(dep[u[i]]%2);
	    }
	}
	else{
	    if(dep[v[i]]<lim)dir[i]=0;
	    else {
		dir[i]=(dep[u[i]]%2)^1;
	    }
	}
    }
    /* for(int i=0;i<n;i++){ */
	/* cerr<<u[i]<<" "<<v[i]<<" "<<dir[i]<<endl; */
    /* } */
    return;
}
mt19937 rnd(114514);
namespace Bobs{
    const int maxn=1e6+5;
    int id[maxn],st[maxn],n,tp[maxn];
    vector<pair<int,bool>>e[maxn];
    int type(int x){
	if(!st[x])e[x]=discover(x),st[x]=1;
	else return tp[x];
	int fl[2]={0,0};
	for(auto [v,tp]:e[x]){
	    fl[tp]|=1;
	}
	if(fl[0]&&fl[1])return 1;
	else return 0;

    }
    int find_a_point(){
	int x=rnd()%n;
	if(type(x)==1){
	    return x;
	}
	else{
	    for(auto [v,tp]:e[x]){
		if(type(v)==0)return find_a_point();
	    }
	    return n+x;
	}
    }
    int find_destination(int x){
	while(type(x)==1){
	    for(auto [v,tp]:e[x]){
		if(tp==0){
		    x=v;break;
		}
	    }
	}
	return x;
    }
}
int Bob (int testid,const int n){
    Bobs::n=n;
    using namespace Bobs;
    int x=find_a_point();
    if(x>n){
	return x-n;
    }
    else{
	return find_destination(x);
    }
}

