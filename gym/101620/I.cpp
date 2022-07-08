#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001,INF=1e9;
int n,a[maxn];
struct seg{
    int mn,pos,tag,ptag;
}t[maxn<<2];
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
void build(int x,int l,int r){
    if(l>r)return;
    if(l==r){
	t[x].pos=l;
	return;
    }
    build(ls,l,mid);
    build(rs,mid+1,r);
}
seg merge(seg a,seg b){
    seg c={INF,INF};
    c.mn=min(a.mn,b.mn);
    if(a.mn==c.mn)c.pos=a.pos;
    else c.pos=b.pos;
    return c;
}
void pushdown(int x){
    if(!t[x].tag)return;
    t[ls].mn+=t[x].tag;t[ls].tag+=t[x].tag;
    t[rs].mn+=t[x].tag;t[rs].tag+=t[x].tag;
    t[x].tag=0;
}
void modify(int x,int l,int r,int L,int R,int v){
    if(l>=L&&r<=R){
	t[x].mn+=v;t[x].tag+=v;return;
    }
    pushdown(x);
    if(L<=mid)modify(ls,l,mid,L,R,v);
    if(R>mid)modify(rs,mid+1,r,L,R,v);
    t[x]=merge(t[ls],t[rs]);
}
void query(int x,int l,int r,int R,int &mn,int &pos){
    if(r<=R){
	if(t[x].mn<mn){
	    mn=t[x].mn;pos=t[x].pos;
	}
	else if(t[x].mn<=mn){
	    pos=min(pos,t[x].pos);
	}
	return;
    }
    pushdown(x);
    query(ls,l,mid,R,mn,pos);
    if(R>mid)query(rs,mid+1,r,R,mn,pos);
}
int mx[maxn],mn[maxn],tp1,tp2,indec;
struct node{
    int l,r,pl,pr,type,id;
    vector<int>e;
}g[maxn];
int check(node a,int l,int r){
    if(g[a.e[0]].l<g[a.e[1]].l){
	return l==a.r+1;
    }
    else return a.l==r+1;
}
void add(node &a,node b){
    a.r=max(a.r,b.r);
    a.l=min(a.l,b.l);
    a.pr=max(a.pr,b.pr);
    a.e.push_back(b.id);
}
int st[maxn],id[maxn],rt;
int top;
void insert(int pos,int v){
    ++indec;id[pos]=indec;
    node cur={v,v,pos,pos,0,indec};
    g[indec]=cur;
    while(top){
	if(g[st[top]].type&&check(g[st[top]],cur.l,cur.r)){
	    add(g[st[top]],cur);
	    cur=g[st[top]];--top;
	}
	else{
	    int res=n+1,lim=n+1,fl=0;
	    query(1,1,n,cur.pr,res,lim);
	    if(res!=-1)break;
	    int mx=cur.r,mn=cur.l,len=cur.r-cur.l+1;
	    for(int tp=top;len<pos-lim+1;--tp){
		mx=max(mx,g[st[tp]].r);mn=min(mn,g[st[tp]].l);len+=g[st[tp]].r-g[st[tp]].l+1;
		if(len-(mx-mn)==1){
		    rt=++indec;
		    g[indec]={mn,mx,pos-len+1,pos,(tp==top),indec};
		    for(int i=tp;i<=top;i++){
			g[indec].e.push_back(st[i]);
		    }
		    g[indec].e.push_back(cur.id);
		    top=tp-1;
		    cur=g[indec];
		    fl=1;
		    break;
		}
	    }
	    if(!fl)break;
	}
    }
    st[++top]=cur.id;
}
int dep[maxn],fa[maxn][19];
void dfs(int x,int pre){
    fa[x][0]=pre;
    dep[x]=dep[pre]+1;
    for(int k=1;k<=18;k++){
	fa[x][k]=fa[fa[x][k-1]][k-1];
    }
    for(auto v:g[x].e){
	dfs(v,x);
    }
}
int get_lca(int x,int y){
    if(dep[x]>dep[y])swap(x,y);
    for(int k=18;k>=0;k--)if(dep[fa[y][k]]>=dep[x])y=fa[y][k];
    if(x==y)return x;
    else{
	for(int k=18;k>=0;k--)if(fa[x][k]!=fa[y][k])x=fa[x][k],y=fa[y][k];
	return fa[x][0];
    }
}
void query(int x,int y){
    x=id[x],y=id[y];
    int lca=get_lca(x,y);
    for(int k=18;k>=0;k--)if(dep[fa[x][k]]>dep[lca])x=fa[x][k];
    for(int k=18;k>=0;k--)if(dep[fa[y][k]]>dep[lca])y=fa[y][k];
    auto l=lower_bound(g[lca].e.begin(),g[lca].e.end(),x);
    auto r=lower_bound(g[lca].e.begin(),g[lca].e.end(),y);
    if(g[lca].type==0){
	printf("%d %d\n",g[lca].pl,g[lca].pr);
    }
    else{
	printf("%d %d\n",g[*l].pl,g[*r].pr);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    build(1,1,n);
    for(int i=1;i<=n;i++){
	modify(1,1,n,1,i,-1);
	modify(1,1,n,mx[tp1]+1,i,a[i]);
	while(tp1&&a[mx[tp1]]<a[i]){
	    modify(1,1,n,mx[tp1-1]+1,mx[tp1],a[i]-a[mx[tp1]]);
	    --tp1;
	}
	mx[++tp1]=i;
	modify(1,1,n,mn[tp2]+1,i,-a[i]);
	while(tp2&&a[mn[tp2]]>a[i]){
	    modify(1,1,n,mn[tp2-1]+1,mn[tp2],-a[i]+a[mn[tp2]]);
	    --tp2;
	}
	mn[++tp2]=i;
	int res=n+1,lim=n+1;
	query(1,1,n,i,res,lim);
	insert(i,a[i]);
    }
    dfs(st[top],0);
    int Q;
    scanf("%d",&Q);
    while(Q--){
	int x,y;scanf("%d%d",&x,&y);
	query(x,y);
    }
}
