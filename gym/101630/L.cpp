#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m;
vector<int>e[maxn];
array<int,maxn>fa,sz,dep,top,son,dfn;
void dfs(int x,int pre){
    fa[x]=pre;
    sz[x]=1;
    dep[x]=dep[pre]+1;
    for(int &v:e[x]){
	if(v==pre)continue;
	dfs(v,x);
	sz[x]+=sz[v];
	if(sz[v]>sz[son[x]])son[x]=v;
    }
}

int indec;
void dfs(int x,int fa,int tp){
    top[x]=tp;
    dfn[x]=++indec;
    /* cout<<"dfs: "<<x<<' '<<fa<<" "<<tp<<"  "<<dfn[x]<<endl; */

    if(son[x])dfs(son[x],x,tp);
    for(int &v:e[x]){
	if(v==fa||v==son[x])continue;
	dfs(v,x,v);
    }
}
int get_lca(int x,int y){
    while(top[x]!=top[y]){
	if(dep[top[x]]<dep[top[y]])swap(x,y);
	x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    return x;
}

int get_dis(int x,int y){
    int z=get_lca(x,y);
    return dep[x]+dep[y]-2*dep[z];
}

vector<pair<int,int>>que;
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)/2)
struct seg{
    int val,tag;
};
seg t[maxn<<2];
void pushup(int x){
    if(t[ls].val<0||t[rs].val<0||t[ls].val!=t[rs].val){
	t[x].val=-2;
    }
    else t[x].val=t[ls].val;
}
void pushdown(int x){
    if(!t[x].tag)return;
    t[rs].tag=t[ls].tag=t[rs].val=t[ls].val=t[x].tag;
    t[x].tag=0;
}
void query(int x,int l,int r,int L,int R,int &cur){
    if(l>=L&&r<=R){
	/* cout<<"get "<<l<<" "<<r<<' '<<cur<<" "<<t[x].val<<endl; */
	if(cur==-2);
	else if(cur==-1)cur=t[x].val;
	else if(t[x].val!=cur)cur=-2;
    }
    else{
	pushdown(x);
	if(L<=mid)query(ls,l,mid,L,R,cur);
	if(R>mid)query(rs,mid+1,r,L,R,cur);
    }
}
void modify(int x,int l,int r,int L,int R,int v){
    /* if(x==1){ */
	/* cout<<"modify "<<L<<" "<<R<<" "<<v<<endl; */
    /* } */
    if(l>=L&&r<=R){
	t[x].val=t[x].tag=v;
    }
    else{
	pushdown(x);
	if(L<=mid)modify(ls,l,mid,L,R,v);
	if(R>mid)modify(rs,mid+1,r,L,R,v);
	pushup(x);
    }
}
int cc=0;
void modify(int x,int y){
    ++cc;
    while(top[x]!=top[y]){
	if(dep[top[x]]<dep[top[y]])swap(x,y);
	modify(1,1,n,dfn[top[x]],dfn[x],cc);
	x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    modify(1,1,n,dfn[x],dfn[y],cc);
}
int check(int x,int y){
    /* cout<<"check "<<x<<' '<<y<<endl; */
    int lst=-1,c;
    while(top[x]!=top[y]){
	if(dep[top[x]]<dep[top[y]])swap(x,y);
	c=-1;query(1,1,n,dfn[top[x]],dfn[x],c);
	/* cout<<top[x]<<" "<<x<<" "<<c<<endl; */
	if(c==-2)return 0;
	if(lst==-1)lst=c;
	if(c!=lst)return 0;
	x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    c=-1;query(1,1,n,dfn[x],dfn[y],c=-1);
    /* cout<<x<<" "<<y<<" "<<c<<endl; */
    if(c==-2)return 0;
    if(lst==-1)lst=c;
    if(c!=lst)return 0;
    return 1;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){
	int x,y;
	scanf("%d%d",&x,&y);
	e[x].push_back(y);
	e[y].push_back(x);
    }
    dfs(1,0);
    dfs(1,0,1);
    for(int i=1;i<=m;i++){
	int x,y;scanf("%d%d",&x,&y);
	que.push_back({x,y});
	/* cout<<get_dis(x,y)<<endl; */
    }
    /* for(int i=1;i<=n;i++)cout<<dfn[i]<<' ';cout<<endl; */

    sort(que.begin(),que.end(),[](auto a,auto b){return get_dis(a.first,a.second)>get_dis(b.first,b.second);});
    for(auto [x,y]:que){
	/* cout<<x<<" "<<y<<endl; */
	if(!check(x,y)){
	    puts("No");
	    return 0;
	}
	modify(x,y);
    }
    puts("Yes");
}
