#include<bits/stdc++.h>
using namespace std;
const int maxn=200010,inf=1e9;
set<int>tg[maxn<<2];
unordered_set<int>hv[maxn<<2];
int t[maxn<<3];
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
void build(int u,int l,int r){
    t[u]=inf,tg[u].insert(inf);
    if(l==r){
	t[u<<1]=t[u<<1|1]=inf;
	return;
    }
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
}
void pushup(int x){
    t[x]=min(max(t[ls],t[rs]),*tg[x].begin());
}
void pushdown(int x,int v){
    tg[ls].insert(v),hv[ls].insert(v),tg[rs].insert(v),hv[rs].insert(v),tg[x].erase(v);
}
void insert(int x,int l,int r,int L,int R,int c){
    if(!hv[x].count(c)) return;
    if(tg[x].count(c)){
        if(L<=l && r<=R){tg[x].erase(c),hv[x].erase(c),pushup(x);return;}
	pushdown(x,c);
	pushup(ls);pushup(rs);
    }
    if(L<=mid) insert(ls,l,mid,L,R,c);
    if(R>mid) insert(rs,mid+1,r,L,R,c);
    if(!hv[ls].count(c)&&!hv[rs].count(c))hv[x].erase(c);
    pushup(x);
}
int qry(int x,int l,int r,int L,int R){
    if(L<=l&&r<=R)return t[x];
    int v=0;
    if(L<=mid)v=max(v,qry(ls,l,mid,L,R));
    if(R>mid)v=max(v,qry(rs,mid+1,r,L,R));
    return min(v,*tg[x].begin());
}
int main(){
    freopen("set.in","r",stdin);
    freopen("set.out","w",stdout);
    int n,m;scanf("%d%d",&n,&m),++n;
    build(1,0,n-1);
    for(int i=0;i<=m;i++)tg[1].insert(i),hv[1].insert(i);t[1]=0;
    int las=0;
    for(int i=1;i<=m;i++){
        int op,l,r,x;scanf("%d%d%d",&op,&l,&r);
        l^=las,r^=las;
        if(op==1){
            scanf("%d",&x),x^=las;
            if(x<=m) insert(1,0,n-1,l,r,x);
        }
        else printf("%d\n",las=qry(1,0,n-1,l,r));
    }
    return 0;
}
