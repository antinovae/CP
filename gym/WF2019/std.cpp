#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define N 510000
#define NN 1100000
#define NNN 2100000
#define NNNN 4100000
using namespace std;
const int inf=999999999;
template<class T>
inline void zwap(T &x,T &y){T z=x;x=y;y=z;}
inline int mymin(int x,int y){return x<y?x:y;}
inline int mymax(int x,int y){return x>y?x:y;}
inline int getz(){
    int x=0,f=1;char c=getchar();
    while(c>'9' || c<'0')c=='-'?f=-1:1,c=getchar();
    while(c<='9' && c>='0')x=(x<<3)+(x<<1)+(c-'0'),c=getchar();
    return f==-1?-x:x;
}
int *id[NN];double be[NNN];
struct node{int x,y;};
inline node makenode(int x,int y){node z;z.x=x;z.y=y;return z;}
struct line{node x,y;int id;}li[N];
inline line makeline(node x,node y){line z;z.x=x;z.y=y;return z;}
inline double findy(line x,double y){
    double bili=(y-be[x.x.x])*1.0/(be[x.y.x]-be[x.x.x]);
    return x.x.y+(x.y.y-x.x.y)*bili;
}
double nowtim;
inline bool operator<(line x,line y){return findy(x,nowtim)<findy(y,nowtim);}
set<line> fuck;
int bel[NNN],type[NNN];
struct Segment{
    int lc,rc,d;
    int type,minlazy;
    int sumlazy,val;
}tr[NNNN];int len;
inline void updata(int x){tr[x].val=mymin(tr[tr[x].lc].val,tr[tr[x].rc].val);}
inline void pushlazy1(int x,int k){tr[x].val+=k;if(tr[x].d!=1)tr[x].sumlazy+=k,tr[x].minlazy+=k;}
inline void pushlazy2(int x,int k){tr[x].val=mymin(tr[x].val,k);if(tr[x].d!=1)tr[x].minlazy=mymin(tr[x].minlazy,k);}
inline void pushlazy3(int x,int type){
    if(tr[x].d!=1){
        if(type==1)pushlazy2(tr[x].rc,tr[tr[x].lc].val);
        else pushlazy2(tr[x].lc,tr[tr[x].rc].val);
        tr[x].type|=type;
        if(tr[x].type==3)tr[x].type=0,pushlazy2(tr[x].lc,tr[tr[x].rc].val),pushlazy2(tr[x].rc,tr[tr[x].lc].val);
    }
}
inline void pushdown(int x){
    pushlazy1(tr[x].lc,tr[x].sumlazy);pushlazy1(tr[x].rc,tr[x].sumlazy);tr[x].sumlazy=0;
    pushlazy2(tr[x].lc,tr[x].minlazy);pushlazy2(tr[x].rc,tr[x].minlazy);tr[x].minlazy=inf;
    if(tr[x].type)pushlazy3(tr[x].lc,tr[x].type),pushlazy3(tr[x].rc,tr[x].type),tr[x].type=0;
}
void bt(int l,int r){
    int x=++len;tr[x].d=r-l+1;tr[x].minlazy=tr[x].val=inf;
    if(l<r){
        int mid=(l+r)>>1;
        tr[x].lc=len+1;bt(l,mid);
        tr[x].rc=len+1;bt(mid+1,r);
    }
}
int fuval;
void change(int x,int l,int r,int ll,int rr,int type){
    if(l==ll && r==rr){
        if(type==0)pushlazy1(x,fuval);
        else pushlazy2(x,fuval),pushlazy3(x,type),fuval=tr[x].val;
        return ;
    }
    pushdown(x);
    int mid=(l+r)>>1;
    if(rr<=mid)change(tr[x].lc,l,mid,ll,rr,type);
    else if(mid<ll)change(tr[x].rc,mid+1,r,ll,rr,type);
    else{
        if(type!=2){change(tr[x].lc,l,mid,ll,mid,type);change(tr[x].rc,mid+1,r,mid+1,rr,type);}
        else {change(tr[x].rc,mid+1,r,mid+1,rr,type);change(tr[x].lc,l,mid,ll,mid,type);}
    }
    updata(x);
}
struct Edge{
    int y,next;
}a[NN];int cnt,last[N],in[N];
int list[N],head,tail;
inline void ins(int x,int y){cnt++;a[cnt].y=y;a[cnt].next=last[x];last[x]=cnt;in[y]++;}
int fl,fr,n;
inline bool cmp(int *x,int *y){return (*x)<(*y);}
int main(){
    //freopen("std.in","r",stdin);
    fl=getz();fr=getz();n=getz();id[n+n+1]=&fl;id[n+n+2]=&fr;
    for(int i=1;i<=n;i++){
        int x1=getz(),y1=getz(),x2=getz(),y2=getz();
        if(x1>x2)zwap(x1,x2),zwap(y1,y2);
        li[i]=makeline(makenode(x1,y1),makenode(x2,y2));
        id[i+i-1]=&li[i].x.x,id[i+i]=&li[i].y.x;
        li[i].id=i;
    }
    sort(id+1,id+n+n+3,cmp);
    for(int i=1;i<=n+n+2;i++){be[i+i-1]=(*id[i]);(*id[i])=i+i-1;}
    for(int i=1;i<=n;i++)bel[li[i].x.x]=bel[li[i].y.x]=i,type[li[i].x.x]=1,type[li[i].y.x]=2;
    int tot=n+n+n+n+3;
    for(int i=2;i<tot;i+=2)be[i]=(be[i-1]+be[i+1])/2;
    for(int i=1;i<=tot;i++){
        nowtim=be[i];
        if(type[i]==2)fuck.erase(li[bel[i]]);
        else if(type[i]==1){
            set<line>::iterator x,y;x=y=(fuck.insert(li[bel[i]])).first;
            if(x!=fuck.begin())x--,ins((*x).id,bel[i]);
            y++;if(y!=fuck.end())ins(bel[i],(*y).id);
        }
    }
    head=1;for(int i=1;i<=n;i++){if(!in[i])list[++tail]=i;}
    while(head<=tail){
        int x=list[head++];
        for(int k=last[x];k;k=a[k].next){
            int y=a[k].y;in[y]--;
            if(!in[y])list[++tail]=y;
        }
    }
    bt(1,tot);
    fuval=-inf;change(1,1,tot,fl,fr,0);
    for(int i=1;i<=tail;i++){
        int x=list[i];
        fuval=1;change(1,1,tot,li[x].x.x+1,li[x].y.x-1,0);
        if(li[x].x.y<li[x].y.y)fuval=inf,change(1,1,tot,li[x].x.x,li[x].y.x-1,1);
        else fuval=inf,change(1,1,tot,li[x].x.x+1,li[x].y.x,2);
    }
    fuval=inf;change(1,1,tot,fl,fr,1);
    printf("%d\n",fuval);
    return 0;
}
