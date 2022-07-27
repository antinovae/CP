#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1000001,INF=1e14;
int n,m,a[maxn];
vector<int>e[maxn];
struct node{
    int x,y,id;
    bool operator < (node a) const {
	int t1=(y>=x),t2=(a.y>=a.x);
	if(t1!=t2)return t1>t2;
	else if(t1){
	    if(x!=a.x)return x<a.x;
	    else return id<a.id;
	}
	else {
	    if(y!=a.y)return y>a.y;
	    else return id<a.id;
	}
    }
}t[maxn];
int fa[maxn],rt[maxn];
set<node>q;
void push(int x,int y,int id){
    t[id]={x,y,id};
    if(fa[id])q.insert(t[id]);
}
void dfs(int x,int p){
    fa[x]=p;
    for(auto v:e[x]){
	if(v!=p)dfs(v,x);
    }
}
int find(int x){
    if(rt[x]==x)return x;
    else return rt[x]=find(rt[x]);
}
void _main(){
    int to;
    scanf("%lld%lld",&n,&to);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<n;i++){
	int x,y;
	scanf("%lld%lld",&x,&y);
	e[x].push_back(y);
	e[y].push_back(x);
    }
    ++n;
    a[n]=INF;
    e[to].push_back(n);
    dfs(1,0);
    for(int i=1;i<=n;i++)rt[i]=i;
    t[1]={0,a[1],1};
    for(int i=2;i<=n;i++){
	if(a[i]>=0){
	    push(0,a[i],i);
	}
	else push(-a[i],0,i); 
    }
    while(!q.empty()){
	auto [x,y,id]=*q.begin();
	auto [px,py,p]=t[find(fa[id])];
	q.erase(t[id]);
	if(fa[p])q.erase(t[p]);
	rt[id]=p;
	if(py-px-x<-px){
	    px=-(py-px-x);
	    py=y;
	}
	else{
	    py=py-x+y;
	}
	push(px,py,p);
    }
    if(t[1].x==0)puts("escaped");
    else puts("trapped");
    q.clear();
    for(int i=1;i<=n;i++){
	e[i].resize(0);
    }
}
signed main(){
    int T;
    scanf("%lld",&T);
    while(T--){
	_main();
    }
}
