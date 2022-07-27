#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
vector<int>e[maxn],g[maxn];
vector<int>ans;
std::stringstream out;
int out_cnt = 0;
void merge(int x,int y){
    ++out_cnt;
    out<<"j "<<x<<' '<<y<<'\n';
    /* cout<<"merge "<<x<<' '<<y<<'\n'; */
}
void link(int c,int x,int y){
    ++out_cnt;
    out<<"c "<<c<<" "<<x<<' '<<y<<'\n';
    /* cout<<"link "<<c<<" "<<x<<' '<<y<<'\n'; */
}
void modify(int c,int x,int y){
    ++out_cnt;
    out<<"r "<<c<<" "<<x<<' '<<y<<'\n';
    /* cout<<"modify "<<c<<" "<<x<<' '<<y<<'\n'; */
}
int dfn[maxn],low[maxn],sqr,st[maxn],top,indec;
void tarjan(int x,int fa){
    dfn[x]=low[x]=++indec;
    st[++top]=x;
    for(auto v:g[x]){
	if(!dfn[v]){
	    tarjan(v,x);
	    low[x]=min(low[x],low[v]);
	    if(low[v]==dfn[x]){
		vector<int>s;
		while(st[top]!=v){
		    s.push_back(st[top--]);
		}
		s.push_back(st[top--]);
		if(s.size()<=1)
		    e[x].push_back(s[0]),e[s[0]].push_back(x);
		else{
		    ++sqr;
		    for(auto v:s)
			e[sqr].push_back(v),e[v].push_back(sqr);
		    e[sqr].push_back(x),e[x].push_back(sqr);
		}
	    }
	}
	else{
	    if(dfn[v]<dfn[x]){
		low[x]=min(low[x],dfn[v]);
	    }
	}
    }
}
int n,m,vis[maxn];
void dfs(int x){
    /* cout<<"dfs "<<x<<endl; */
    vis[x]=1;
    if(x<=n){
	//circle
	for(auto v:e[x]){
	    if(vis[v])continue;
	    dfs(v);
	    if(v<=n){
		merge(x,v);link(x,1,2);
		modify(x,2,3);
	    }
	    else{
		int p=0;
		for(auto u:e[v])if(u!=x)p=u;
		merge(x,p);
		link(x,1,2);link(x,1,4);
		modify(x,2,3);modify(x,4,3);
	    }
	}
	modify(x,1,2);
    }
    else{
	int l=0,r=0;
	for(auto v:e[x]){
	    if(vis[v])continue;
	    dfs(v);
	    if(!l){
		l=v;
		modify(v,2,1);
	    }
	    else if(!r){
		merge(l,v);
		r=v;modify(v,2,4);
		link(v,1,4);
	    }
	    else{
		merge(r,v);link(r,2,4);
		modify(r,4,3);modify(r,2,4);
		r=v;
	    }
	}
	modify(r,1,2);
    }
}
int main(){
    freopen("cactus.in","r",stdin);
    freopen("cactus.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
	int k,x,lst=0;
	scanf("%d",&k);
	for(int j=1;j<=k;j++){
	    scanf("%d",&x);
	    if(lst)g[x].push_back(lst),g[lst].push_back(x);
	    lst=x;
	}
    }
    sqr=n;
    tarjan(1,0);
    /* for(int i=1;i<=sqr;i++){ */
	/* for(auto v:e[i])cout<<i<<" "<<v<<endl; */
    /* } */
    dfs(1);

    std::cout<<out_cnt<<std::endl;
    std::cout<<out.rdbuf();
}
