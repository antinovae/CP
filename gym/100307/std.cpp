#include<bits/stdc++.h>
using namespace std;
const int maxn=300005;
int n,m,ans[maxn],sz[maxn],fa[maxn],f[maxn];
set<pair<int,int>>s;
struct node{
    int x,y,id;
}a[maxn<<1];
int find(int x){return x==f[x]?x:f[x]=find(f[x]);}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i) {
	int x,y;scanf("%d%d",&x,&y);
	a[i]={2*x-1,2*y-1,0};
    }
    scanf("%d",&m);
    for(int i=1;i<=m;++i){
	int x,y;
	scanf("%d%d",&x,&y);
	a[i+n]={2*x,2*y,i};
	f[i]=i;
    }
    sort(a+1,a+n+m+1,[&](node a,node b){return a.y>b.y;});
    for(int i=1;i<=n+m;++i){
	if(!a[i].id){
	    auto it=s.lower_bound({a[i].x,0});
	    if(it!=s.end())++sz[it->second];
	}
	else{
	    auto x=(pair<int,int>){a[i].x,a[i].id};
	    auto it=s.insert(x).first;
	    while(it!=s.begin()&&prev(it)->second>a[i].id)s.erase(prev(it));
	    if(next(it)!=s.end()){
		fa[a[i].id]=next(it)->second;
	    }
	}
    }
    for(int i=m;i;i--){
	int x=find(i);
	ans[i]=sz[x];
	if(fa[i]){
	    int p=find(fa[i]);
	    sz[p]+=sz[x];f[x]=p;
	}
    }
    for(int i=1;i<=m;++i) printf("%d\n",ans[i]);
}

