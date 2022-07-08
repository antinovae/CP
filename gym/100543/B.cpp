#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=100001;
struct point{
    int x,y;
    point operator - (point b){
	return {x-b.x,y-b.y};
    }
}p[maxn];
struct line{
    int a,b,c;
    int id;
    line(){a=0,b=0,c=0;}
    line(point p1,point p2){
	a=p1.y-p2.y;
	b=p2.x-p1.x;
	c=-(a*p1.x+b*p1.y);
    }
    int cal(point p){
	return a*p.x+b*p.y+c;
    }
}ln[maxn];
int cross(point a,point b){
    return a.x*b.y-a.y*b.x;
}
int n,a[maxn],b[maxn];
struct seg{
    vector<point>s;
    int cal(line a){
	while(s.size()>=2&&a.cal(*--s.end())<a.cal(*prev(s.end(),2)))
	    s.pop_back();
	return a.cal(s.back());
    }
}t[maxn<<2];
seg merge(seg a,seg b){
    seg c=a;
    for(auto v:b.s){
	while(c.s.size()>=2&&cross(v-*(--c.s.end()),v-*prev(c.s.end(),2))<0){
	    c.s.pop_back();
	}
	c.s.push_back(v);
    }
    return c;
}
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
void build(int x,int l,int r){
    if(l==r){t[x].s.clear();t[x].s.push_back(p[l]);return;}

    if(l<=mid)build(ls,l,mid);
    if(r>mid)build(rs,mid+1,r);
    t[x]=merge(t[ls],t[rs]);
}
int beats(int x,int l,int r,const line &ln,int &ans){
    if(t[x].cal(ln)<=0)return 0;
    if(l==r){
	ans=l;
	return 1;
    }
    if(beats(ls,l,mid,ln,ans))return 1;
    else return beats(rs,mid+1,r,ln,ans);
}
int query(int x,int l,int r,const int &pos,const line &ln,int &ans){
    if(pos>r||l>r)return 0;
    if(l>pos){
	return beats(x,l,r,ln,ans);
    }
    if(pos<mid&&query(ls,l,mid,pos,ln,ans))return 1;
    return query(rs,mid+1,r,pos,ln,ans);
}
int ans[maxn];
void _main(){
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
	ans[i]=0;
	scanf("%lld%lld",&p[i].x,&p[i].y);
	if(i>1){
	    ln[i]=line(p[i-1],p[i]);
	    ln[i].id=i;
	}
    }
    build(1,1,n);
    sort(ln+2,ln+1+n,[&](line p1,line p2){
	    return cross({p1.a,p1.b},{p2.a,p2.b})>0;
	    });
    for(int i=2;i<=n;i++){
	query(1,1,n,ln[i].id,ln[i],ans[ln[i].id]);
    }
    for(int i=2;i<=n;i++){
	if(ans[i]==0)printf("%d ",0);
	else printf("%lld ",ans[i]-1);
    }
    puts("");
}

signed main(){
    int T;
    scanf("%lld",&T);
    while(T--){
	_main();
    }
}
