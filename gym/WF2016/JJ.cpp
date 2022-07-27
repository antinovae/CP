#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=250010;
int n,m,ce,i,j,x,y,z,ca,cb,cnt,ret,mv;
struct point{
    int x,y;
    point operator-(const point&b){return {x-b.x,y-b.y};}
    void operator-=(const point&b){*this=*this-b;}
    bool operator==(const point&b){return x==b.x&&y==b.y;}
    bool operator!=(const point&b){return x!=b.x||y!=b.y;}
}a[N],b[N],c[N<<1];
struct E{
    point o;int t;
    E(){}
    E(point _o,int _t){
	o=_o,t=_t;
	if(o.x<0)o.x*=-1,o.y*=-1;
    }
}e[N<<1];
bool cmp(const point&a,const point&b){return a.x==b.x?a.y<b.y:a.x<b.x;}
int cross(const point&a,const point&b){return 1LL*a.x*b.y-1LL*a.y*b.x;}
bool cmpe(const E&a,const E&b){return cross(a.o,b.o)<0;}
void read(int&a){char c;while(!(((c=getchar())>='0')&&(c<='9')));a=c-'0';while(((c=getchar())>='0')&&(c<='9'))(a*=10)+=c-'0';}
int convexhull(point*p,int n,point*q){
    int i,k,m;
    for(i=m=0;i<n;q[m++]=p[i++])while(m>1&&cross(q[m-1]-q[m-2],p[i]-q[m-2])<=0)m--;
    k=m;
    for(i=n-2;i>=0;q[m++]=p[i--])while(m>k&&cross(q[m-1]-q[m-2],p[i]-q[m-2])<=0)m--;
    return --m;
}
bool point_on_segment(point p,point a,point b){
    return !cross(b-a,p-a)&&1LL*(p.x-a.x)*(p.x-b.x)+1LL*(p.y-a.y)*(p.y-b.y)<=0;
}
int askl(int l,int r,point p){
    int t=l++,mid;
    while(l<=r){
	mid=(l+r)>>1;
	if(cross(c[mid]-p,c[(mid-1+n)%n]-c[mid])<=0)l=(t=mid)+1;else r=mid-1;
    }
    return t;
}
int askr(int l,int r,point p){
    int t=r--,mid;
    while(l<=r){
	mid=(l+r)>>1;
	if(cross(c[mid]-p,c[(mid+1)%n]-c[mid])>=0)r=(t=mid)-1;else l=mid+1;
    }
    return t;
}
void solve(point p){
    if(point_on_segment(p,c[0],c[n-1])){cnt++;return;}
    int o=0;
    if(p.x>0){
	int l=1,r=n-1,mid;
	while(l<=r)if(cross(c[mid=(l+r)>>1],p)>=0)l=(o=mid)+1;else r=mid-1;
    }else if(p.y>0)o=n-1;
    if(p.x>=0&&cross(p-c[o],c[o+1]-p)<0){cnt++;return;}
    if(p.x>=0&&point_on_segment(p,c[o],c[o+1])){cnt++;return;}
    int l,r;
    if(p.x>0)l=askl(0,o,p),r=askr(o,n,p);else l=askl(m,n,p),r=askr(0,m,p);
    e[++ce]=E(p-c[l],1);
    e[++ce]=E(p-c[r],-1);
    if(cmpe(e[ce],e[ce-1]))cnt++;
}
signed main(){
    read(n);
    while(n--){
	read(x),read(y),read(z);
	if(z)a[++ca]={x,y};else b[++cb]={x,y};
    }
    if(ca==1)return puts("1"),0;
    cnt=ca;
    sort(a+1,a+ca+1,cmp);
    for(ca=0,i=1;i<=cnt;i++)if(i==1||a[i]!=a[i-1])a[++ca]=a[i];
    if(ca==1){
	for(i=1;i<=cb;i++)if(b[i]==a[1])cnt++;
	return printf("%lld",cnt),0;
    }
    if(ca==2){
	for(i=1;i<=cb;i++)if(point_on_segment(b[i],a[1],a[2]))cnt++;
	return printf("%lld",cnt),0;
    }
    n=convexhull(a+1,ca,c);
    for(i=1;i<n;i++)c[i]-=c[0];
    for(i=1;i<=cb;i++)b[i]-=c[0];
    c[0]-=c[0];
    for(i=0;i<n;i++)if(c[i].x>=c[m].x)m=i;
    for(i=0;i<n;i++)c[i+n]=c[i];
    for(i=1;i<=cb;i++)solve(b[i]);
    sort(e+1,e+ce+1,cmpe);
    for(i=1;i<=ce;i=j){
	for(j=i;j<=ce&&!cross(e[i].o,e[j].o);j++)ret+=e[j].t;
	if(ret<mv)mv=ret;
    }
    return printf("%lld",cnt+mv),0;
}
