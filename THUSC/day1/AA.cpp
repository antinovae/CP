#include<bits/stdc++.h>
using namespace std;
const int maxn=1001;
double p[maxn],sp[maxn];
int dis[maxn],vis[maxn];
int n,m,K,beg,ed,t[maxn];
struct asuka{
    int y,l,a,b;
};
vector<asuka>e[maxn];
void dij(){
    memset(dis,127/3,sizeof(dis));
    dis[ed]=0;
    for(int day=1;day<=n;day++){
	int x=0;
	for(int i=1;i<=n;i++){
	    if(dis[i]<dis[x]&&!vis[i])x=i;
	}
        if(!x)return;
	vis[x]=1;
	for(auto [v,l,a,b]:e[x]){
	    dis[v]=min(dis[v],dis[x]+b*l);
	}
    }
}
unordered_map<int,double>f[maxn];
int in[maxn][maxn*10];
const double eps=1e-8;
int le(double a,double b){
    if(fabs(a-b)<=eps)return 0;
    return a<n;
}
queue<pair<int,int>>q;
void spfa(){
    /* cout<<f[0][0]<<endl; */
    for(int i=K;i>=0;i--)sp[i]=sp[i+1]+p[i];
    for(int i=10000;i>=0;i--){
	f[ed][i]=0;
	in[ed][i]=1;
	q.push({ed,i});
    }
    while(!q.empty()){
	auto [x,R]=q.front();q.pop();
	/* cout<<x<<" "<<R<<" "<<f[x][R]<<endl; */
	in[x][R]=0;
	for(auto [v,l,a,b]:e[x]){
	    int L=R-l;
	    if(L<0)continue;
	    /* cout<<v<<" to "<<x<<" range "<<L<<" "<<R<<endl; */
	    int j=upper_bound(t+1,t+1+K,L)-t;
	    double res=0,pp=1;
	    for(int i=j;t[i]<=R&&i<=K;i++){
		/* cout<<p[i]<<" "<<sp[j]<<" "<<(t[i]-L)*a<<" "<<(R-t[i])*b<<" "<<dis[x]<<endl; */
		res+=p[i]/sp[j]*((t[i]-L)*a+(R-t[i])*b+dis[x]);
		pp-=p[i]/sp[j];
	    }
	    res+=pp*(f[x][R]+l*a);
	    if(f[v].find(L)==f[v].end()||le(res,f[v][L])==1){
		f[v][L]=res;
		/* cout<<"upd "<<v<<" "<<L<<" "<<res<<endl; */
		if(!in[v][L])q.push({v,L}),in[v][L]=1;
	    }
	}
	/* break; */
    }
}
int main(){
    scanf("%d%d%d%d%d",&n,&m,&K,&beg,&ed);
    for(int i=1;i<=m;i++){
	int x,y,l,a,b;
	scanf("%d%d%d%d%d",&x,&y,&l,&a,&b);
	e[x].push_back({y,l,a,b});
	e[y].push_back({x,l,a,b});
    }
    double sm=0;
    for(int i=1;i<=K;i++){
	scanf("%d%lf",&t[i],&p[i]);
	sm+=p[i];
    }
    dij();
    spfa();
    printf("%.10lf",f[beg][0]);
}
