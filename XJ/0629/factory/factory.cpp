#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=205,mo=1e9+7;
vector<int>e[N];
int qpow(int a,int b){
    int res=1;
    for(;b;b>>=1,a=1ll*a*a%mo)
	if(b&1)res=1ll*res*a%mo;
    return res;
}
bool vis[N];
int fa[N],dep[N],id[N],inv[N],f[N][N],st[N],tot=0,siz[N];
void dfs(int x){
    vis[x]=false;siz[x]=1;
    for(auto v:e[x])
	if(vis[v]){
	    fa[v]=x;
	    dep[v]=dep[x]+1;
	    dfs(v);
	    siz[x]+=siz[v];
	}
}
void pre(int n){
    for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
	    int x=id[i],y=id[j];
	    if(f[x][y]){
		for(auto z:e[x])
		    if(fa[z]==x){
			f[z][y]=(f[z][y]+1ll*f[x][y]*inv[siz[x]+siz[y]-1]%mo*siz[x])%mo;
		    }
		for(auto z:e[y])
		    if(fa[z]==y){
			f[x][z]=(f[x][z]+1ll*f[x][y]*inv[siz[x]+siz[y]-1]%mo*siz[y])%mo;
		    }
	    }
	}
}
int main(){
    freopen("factory.in","r",stdin);
    freopen("factory.out","w",stdout);
    int n,rt;
    scanf("%d%d",&n,&rt);
    for(int i=1;i<n;i++){
	int x,y;
	scanf("%d%d",&x,&y);
	e[x].push_back(y);
	e[y].push_back(x);
    }
    memset(vis,true,sizeof(vis));
    dfs(rt);
    for(int i=1;i<=n;i++) id[i]=i;
    sort(id+1,id+n+1,[](int a,int b){
	    return dep[a]<dep[b];
	    });
    for(int i=0;i<=n;i++) inv[i]=qpow(i,mo-2);
    for(int i=1;i<=n;i++){
	tot=0;
	for(auto y:e[i])
	    if(fa[y]==i) st[++tot]=y;
	for(int j=1;j<=tot;j++)
	    for(int k=1;k<=tot;k++)
		if(j!=k) f[st[j]][st[k]]=1;
    }
    pre(n);
    int ans=0;
    for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++){
	    if(fa[i]==j||fa[j]==i){
		if(fa[i]==j){
		    int x=j,d=1;
		    while(x) d=1ll*d*siz[x]%mo*inv[siz[x]-1]%mo,x=fa[x];
		    ans=(ans+1ll*siz[i]*d%mo*abs(i-j))%mo;
		}
		else{
		    int x=i,d=1;
		    while(x) d=1ll*d*siz[x]%mo*inv[siz[x]-1]%mo,x=fa[x];
		    ans=(ans+1ll*siz[j]*d%mo*abs(i-j))%mo;
		}
	    }
	    else{
		if(f[i][j]){
		    int x=i,y=j;
		    while(dep[x]>dep[y])x=fa[x];
		    while(dep[y]>dep[x])y=fa[y];
		    while(x!=y)x=fa[x],y=fa[y];
		    int d=1;
		    while(x)d=1ll*d*siz[x]%mo*inv[siz[x]-1]%mo,x=fa[x];
		    ans=(ans+1ll*f[i][j]*siz[i]%mo*siz[j]%mo*inv[siz[i]+siz[j]-1]%mo*d*2%mo*abs(i-j))%mo;
		}
	    }
	}

    int d=1;
    for(int i=1;i<=n;i++) d=1ll*d*i%mo*inv[siz[i]]%mo;
    d=1ll*d*inv[n]%mo;
    printf("%d\n",1ll*ans*d%mo);

    return 0;
}  
