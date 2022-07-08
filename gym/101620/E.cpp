#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=500001;
int dfn[maxn],n,x,y,dep[maxn],on[maxn],indec,g[maxn],h[maxn],vis[maxn];
vector<int>e[maxn];
void pre(int x,int fa){
    dfn[x]=++indec;on[indec]=x;
    dep[x]=dep[fa]+1;
    for(auto &v:e[x]){
	if(v==fa)swap(v,e[x].back());
    }
    if(e[x].back()==fa)e[x].pop_back();
    for(auto v:e[x]){
	pre(v,x);
	h[x]=max(h[x],h[v]+1);
    }
    if(e[x].size()==1)g[x]=g[e[x][0]];
    else g[x]=x;
}
int kth(int x,int k){
    return on[dfn[x]-k];
}
const int mo=1e9+7;
int f[maxn];
int dfs(int x);
int para(int x,int y){
    int p=g[x],q=g[y],ans=0;
    if(dep[p]-dep[x]==dep[q]-dep[y]){
	if(e[p].size()==0&&e[q].size()==0)ans+=1;
    }
    else{
	int v=(dep[q]-dep[y])-(dep[p]-dep[x]);
	if(v<0)swap(x,y),swap(p,q),v=-v;
	int z=kth(q,v-1);
	if(e[p].size()==0){
	    (ans+=dfs(z))%=mo;
	}
    }
    return ans;
}
int dfs(int x){
    if(vis[x])return f[x];
    vis[x]=1;
    for(auto v:e[x])dfs(v);
    if(e[x].size()==0){
	f[x]=1;
    }
    else if(e[x].size()>=3){
	f[x]=0;
    }
    else if(e[x].size()==2){
	int y=e[x][0],z=e[x][1];
	auto func=[&]{
	    if(e[z].size()==0)(f[x]+=f[y])%=mo;
	    else if(e[z].size()==1)(f[x]+=para(y,e[z][0]))%=mo;};
	func();swap(y,z);func();
    }
    else{
	int y=e[x][0];
	if(e[y].size()==0)(f[x]+=1)%=mo;
	else if(e[y].size()==1)(f[x]+=f[e[y][0]])%=mo;
	(f[x]+=f[y])%=mo;
	int z=g[y];
	if(e[z].size()==0){
	    if(z!=y&&(dep[z]-dep[y])%2==0)(f[x]+=1)%=mo;
	}
	else if(e[z].size()==2){
	    int p=e[z][0],q=e[z][1];
	    auto func1=[&]{
		if(e[p].size()==1){
		    if(h[p]==dep[z]-dep[x]&&e[g[p]].size()==0)(f[x]+=f[q])%=mo;
		}
		else if(e[p].size()==2){
		    int w1=e[p][0],w2=e[p][1];
		    if(h[w1]+1==dep[z]-dep[x]&&e[g[w1]].size()==0)(f[x]+=para(q,w2))%=mo;
		    if(h[w2]+1==dep[z]-dep[x]&&e[g[w2]].size()==0)(f[x]+=para(q,w1))%=mo;
		}
	    };
	    func1();swap(p,q);func1();swap(p,q);
	    if(y==z)(x+=0);
	    else{
		if(h[p]+2==dep[z]-dep[x]&&e[g[p]].size()==0)(f[x]+=f[q])%=mo;
		if(h[q]+2==dep[z]-dep[x]&&e[g[q]].size()==0)(f[x]+=f[p])%=mo;
	    }
	}
    }
    return f[x];
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<n;i++){
	scanf("%lld%lld",&x,&y);
	e[x].push_back(y);
	e[y].push_back(x);
    }
    pre(1,0);
    dfs(1);
    printf("%lld\n",f[1]%mo);
}
