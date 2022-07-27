#include<bits/stdc++.h>
using namespace std;
const int maxn=5001;
int n,m;
int a[maxn][maxn],to[maxn],vis[maxn];
int nxt(int x,int v){return (((x-1)+v)+n)%n+1;}
int pre(int x){return (((x-1)-1)+n)%n+1;}
int nxt(int x){return (((x-1)+1)+n)%n+1;}
int nxt_y(int y){return ((y-1)+1+m)%m+1;}
int pre_y(int y){return ((y-1)-1+m)%m+1;}
pair<int,int> step(int y,int x){
    int mx=0;
    for(int i:{-1,0,1}){
	if(a[nxt_y(y)][nxt(x,i)]>a[nxt_y(y)][nxt(x,mx)])mx=i;
    }
    return {nxt_y(y),nxt(x,mx)};
}
int find(int y,int x){
    int fl=0;
    while(y!=1||!fl){
	fl=1;
	auto [_y,_x]=step(y,x);
	y=_y,x=_x;
    }
    return x; 
}
int curx=1,cury=1;
void query(int sum){
    int tot=0,cycle=0;
    int x=curx,y=cury;
    for(int i=1;i<=n;i++)vis[i]=-1;
    while(y!=1&&tot<sum){
	++tot;
	auto [_y,_x]=step(y,x);
	y=_y,x=_x;
    }
    while(tot+m<=sum){
	if(vis[x]!=-1){
	    cycle=tot-vis[x];
	    break;
	}
	vis[x]=tot;
	tot+=m;
	x=to[x];
    }
    sum-=tot;if(cycle)sum%=cycle;
    tot=0;
    while(tot+m<=sum){
	tot+=m;
	x=to[x];
    }
    while(tot<sum){
	++tot;
	auto [_y,_x]=step(y,x);
	y=_y,x=_x;
    }
    curx=x,cury=y;
    printf("%d %d\n",x,y);
}
int in(int x,int l,int r){
    if(l<=r)return x>=l&&x<=r;
    else return x>=l||x<=r;
}

void update(int y,int x){
    int ans=find(y,x);
    int l=x,r=x,len=1;
    while(y>1){
	int p=pre(l),q=nxt(r);
	int _l,_r;
	if(len==1){
	    _l=0,_r=0;
	    int le=0,a,b,c;
	    a=in(step(pre_y(y),p).second,l,r);
	    b=in(step(pre_y(y),l).second,l,r);
	    c=in(step(pre_y(y),q).second,l,r);
	    if(a)le++,_r=p;
	    if(b)le++,_r=l;
	    if(c)le++,_r=q;
	    if(c)_l=q;
	    if(b)_l=l;
	    if(a)_l=p;
	    len=le;
	    if(le<=0)break;
	}
	else{
	    _l=l,_r=r;
	    if(!in(step(pre_y(y),l).second,l,r))len--,_l=nxt(l);
	    else if(in(step(pre_y(y),p).second,l,r)){
		len++,_l=pre(l);
	    }
	    if(!in(step(pre_y(y),r).second,l,r))len--,_r=pre(r);
	    else if(in(step(pre_y(y),q).second,l,r))len++,_r=nxt(r);
	}
	l=_l,r=_r;
	y=pre_y(y);
	if(len<=0)break;
	if(len>=n)break;
    }
    if(len<=0){}
    else if(len>=n){
	for(int i=1;i<=n;i++)to[i]=ans;
    }
    else{
	while(l!=r){
	    to[l]=ans;
	    l=nxt(l);
	}
	to[l]=ans;
    }
    return;
}

void modify(int y,int x,int v){
    a[y][x]=v;
    update(pre_y(y),pre(x));
    update(pre_y(y),x);
    update(pre_y(y),nxt(x));
}
char s[10];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)scanf("%d",&a[j][i]);
    for(int i=1;i<=n;i++){
	to[i]=find(1,i);
    }
    int Q;
    scanf("%d",&Q);
    while(Q--){
	scanf("%s",s);
	if(s[0]=='m'){
	    int x;scanf("%d",&x);
	    query(x);
	}
	else{
	    int x,y,v;scanf("%d%d%d",&x,&y,&v);
	    modify(y,x,v);
	}
    }
}
