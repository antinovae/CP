#include<bits/stdc++.h>
using namespace std;
const int maxn=3e5+5;
int n,w[maxn],val[maxn],_w[maxn],id[maxn];
vector<pair<int,int>>e[maxn];
void pr();
struct dp_array{
    vector<int>a;
    int _;
    void init(int x){
	a.resize(2*x+1);
	_=x;
    }
    int& operator[](int x){
	if(x+_>=a.size()||x+_<0)assert(0);
	return a[x+_];
    }
}f[maxn],g[maxn];
int pre[maxn],h[maxn],fe[maxn];
void pre_dfs(int x,int fa){
    pre[x]=fa;
    for(auto [v,w]:e[x]){
	if(v==fa)continue;
	pre_dfs(v,x);
	h[x]=max(h[x],h[v]+1);
    }
    f[x].init(h[x]);
}
void dfs(int x,int fa){
    f[x][0]=1;
    for(auto [v,id]:e[x]){
	if(v==fa)continue;
	fe[v]=id;
	dfs(v,x);
	for(int i=-h[v];i<=h[v];i++){
	    f[x][i+w[id]]+=f[v][i];
	}
    }
    /* cout<<x<<" "<<endl; */
}
int modify(int x){
    /* cout<<"MODIFY "<<x<<endl; */
    int l=0,v=x,ans=0;
    int p=pre[x];
    g[x]=f[x];
    while(p){
	/* cout<<p<<"-> "<<x<<endl; */
	g[p]=f[p];
	for(int i=-h[x];i<=h[x];i++){
	    f[p][i+w[fe[x]]]-=g[x][i];
	}
	l+=_w[fe[x]];
	for(int i=-h[v];i<=h[v];i++){
	    int j=1-(i+l);
	    if(j<=h[p]&&j>=-h[p]){ans+=f[v][i]*f[p][j]; }
	}
	for(int i=-h[x];i<=h[x];i++){
	    f[p][i+_w[fe[x]]]+=f[x][i];
	}
	x=p,p=pre[x];
    }
    return ans;
}
int x[maxn],y[maxn];
void pr(){
    for(int i=1;i<=n;i++){
	cout<<i<<" h: "<<h[i]<<" pre: "<<pre[i]<<endl;
	for(int j=-h[i];j<=h[i];j++){
	    if(f[i][j])cout<<j<<" "<<f[i][j]<<endl;
	}
    }
    cout<<endl;
}
int main(){
    /* freopen("hidden.in","r",stdin); */
    /* freopen("hidden.out","w",stdout); */
    scanf("%d",&n);
    for(int i=1;i<n;i++){
	id[i]=i;
	scanf("%d%d%d",&x[i],&y[i],&val[i]);
	e[x[i]].push_back({y[i],i});e[y[i]].push_back({x[i],i});
    }
    sort(id+1,id+n,[](int x,int y){return val[x]<val[y];});
    for(int i=1;i<n;i++){
	w[i]=_w[i]=-1;
    }
    pre_dfs(1,0);
    dfs(1,0);
    long double sum=0,cnt=0;
    for(int j=1;j<n;j++){
	int i=id[j];
	_w[i]=1;
	/* cout<<x[i]<<" "<<y[i]<<" "<<val[i]<<endl; */
	if(h[x[i]]>h[y[i]])swap(x[i],y[i]);
	int cur=modify(x[i]);
	/* cout<<cur<<endl; */
	sum+=1ll*cur*val[i];
	cnt+=cur;
	w[i]=1;
	if(j%1000==0)pr();
    }
    long double res=sum/cnt;
    printf("%.12Lf",res);
}

