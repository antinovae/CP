#include<bits/stdc++.h>
using namespace std;
const int maxn=2000001,INF=7e8+5;
/* stringstream _cout; */
#define cout _cout
#define cerr _cout
 
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template<typename T>
inline void Read(T &n){
    char ch; bool flag=false;
    while(!isdigit(ch=getchar())) if(ch=='-')flag=true;
    for(n=ch^48; isdigit(ch=getchar()); n=(n<<1)+(n<<3)+(ch^48));
    if(flag) n=-n;
}


int n;
struct node{
    int a,b,c;
}a[maxn];
struct  seg{
    seg *pre;
    int l,r,val,b;
    seg(){
	l=r=val=0;
	b=-1;pre=NULL;
    }
};
int ls[maxn<<3],rs[maxn<<3],rt;
seg *loc[maxn<<3],*tag[maxn<<3];
int idx;
void pushdown(int x){
    if(!tag[x])return;
    if(!ls[x])ls[x]=++idx;
    if(!rs[x])rs[x]=++idx;
    tag[ls[x]]=tag[x];loc[ls[x]]=tag[x];
    tag[rs[x]]=tag[x];loc[rs[x]]=tag[x];
    tag[x]=NULL;
}
seg pool[maxn*2];
void pr(seg *p){
    /* cout<<p-pool<<"  range "<<p->l<<' '<<p->r<<" val "<<p->val<<" bmin "<<p->b<<" pre "<<p->pre-pool<<endl; */
}
void recolor(int &x,int l,int r,int L,int R,seg *v){
    if(!x)x=++idx;
    if(l>=L&&r<=R){
	loc[x]=v;tag[x]=v;
	/* cout<<"put "<<l<<" "<<r<<" "<<v-pool<<endl; */
    }
    else{
	pushdown(x);
	int mid=(l+r)/2;
	if(L<=mid)recolor(ls[x],l,mid,L,R,v);
	if(R>mid)recolor(rs[x],mid+1,r,L,R,v);
    }
}
seg* query(int x,int l,int r,int v){
    if(!x)return NULL;
    if(l==r)return loc[x];
    int mid=(l+r)/2;
    pushdown(x);
    if(v<=mid)return query(ls[x],l,mid,v);
    else return query(rs[x],mid+1,r,v);
}
int indec;
void modify(int loc);
set<pair<int,int>>ans;
void rmv(int res,int p){
    /* cout<<"rmv	    "<<res<<" at "<<p<<endl; */
    ans.erase({res,p});
}
void ins(int res,int p){
    /* cout<<"ins	    "<<res<<" at "<<p<<endl; */
    ans.insert({res,p});
}
void pr(){
    /* cout<<endl; */
    /* for(int i=1;i<=indec;i++)pr(&pool[i]); */
    /* cout<<endl; */
}
void ins(node x){
    auto [a,b,c]=x;
    auto cur=query(rt,0,INF,b);
    /* cout<<endl; */
    /* cout<<"insert "<<a<<' '<<b<<" "<<c<<endl; */
    /* cout<<cur-pool<<endl; */
    pr(cur);
    assert(b>=cur->l);
    if(c>cur->val){
	seg *p=NULL;
	/* if(b>cur->l){ */
	    /* cout<<"split ! "<<endl; */
	    /* cout<<"cur: ";pr(cur); */
	    if(cur->b!=-1)
		rmv(cur->val+cur->b,cur->b);
	    p=&pool[++indec];
	    p->l=cur->l;if(cur->b<b)p->b=cur->b;p->r=b-1;p->val=c;
	    auto pre=cur->pre;
	    cur->l=b;cur->b=b;cur->pre=p;
	    if(cur->b!=-1)
		ins(cur->val+cur->b,cur->b);
	    /* cout<<"cur: ";pr(cur); */
	    /* cout<<"p: ";pr(p); */
	    /* /1* if(pre)cout<<"pre: ",pr(pre); *1/ */
	    /* cout<<endl; */
	    while(pre&&c>=pre->val){
		/* cout<<"find_pre: ";pr(pre); */
		/* cout<<pre-pool<<endl; */
		rmv(pre->val+pre->b,pre->b);
		p->l=pre->l;
		if(pre->b!=-1)
		    p->b=pre->b;
		pre=pre->pre;
	    }
	    if(p->b!=-1)
		ins(p->val+p->b,p->b);
	    recolor(rt,0,INF,p->l,p->r,p);
	    /* if(pre)cout<<"pre: ",pr(pre); */
	    p->pre=pre;
	/* } */
	/* else{ */
	/*     cout<<"not split! "<<endl; */
	/*     /1* cout<<"cur: ";pr(cur); *1/ */
	/*     cur->l=b; */
	/*     if(cur->b)cur->b=min(cur->b,b); */
	/*     else cur->b=b; */ 
	/*     /1* if(cur->b) *1/ */
	/* 	ins(cur->val+cur->b,cur->b); */
	/*     p=cur; */
	/*     cout<<"cur: ";pr(cur); */
	/* } */

	/* exit(0); */
    }
    else{
	if(cur->b!=-1)
	    rmv(cur->val+cur->b,cur->b);
	if(cur->b==-1||b<cur->b){
	    cur->b=b;
	}
	if(cur->b!=-1)
	    ins(cur->val+cur->b,cur->b);
	/* cout<<"cur: ";pr(cur); */

    }
    pr();
}
int _ans;
void cal(int x){
    if(!ans.empty()){
	_ans=min(_ans,x+ans.begin()->first);
	/* cout<<"AHH!"<<endl; */
	/* cout<<ans.begin()->first<<' '<<ans.begin()->second<<endl; */

    }
    else _ans=max(_ans,x);
}
void init(){
    _ans=0;
    ans.clear();
    memset(loc,0,sizeof(loc[0])*(idx+5));
    memset(tag,0,sizeof(tag[0])*(idx+5));
    memset(ls,0,sizeof(ls[0])*(idx+5));
    memset(rs,0,sizeof(rs[0])*(idx+5));
    for(int i=1;i<=indec;i++)pool[i]=seg();
    rt=0;idx=0,indec=0;
    
    
}
void _main(){
    Read(n);
    init();
    for(int i=1;i<=n;i++)Read(a[i].a),_ans=max(_ans,a[i].a);
    for(int i=1;i<=n;i++)Read(a[i].b);
    for(int i=1;i<=n;i++)Read(a[i].c);
    sort(a+1,a+1+n,[](node a,node b){return a.a<b.a;});
    auto p=&pool[++indec];
    /* cout<<pool<<" "<<p-pool<<" "<<&pool[1]-pool<<" "<<&pool[2]-pool<<endl; */

    p->l=0;p->r=INF;
    recolor(rt,0,INF,p->l,p->r,p);
    /* for(int i=1;i<=n;i++){ */
	/* cerr<<a[i].a<<' '<<a[i].b<<" "<<a[i].c<<endl; */
    /* } */
    int curb=0,curc=0;
    for(int i=n;i>=1;i--){
	cal(a[i].a);
	_ans=min(_ans,a[i].a+curb);
	_ans=min(_ans,a[i].a+curc);
	curb=max(curb,a[i].b);
	curc=max(curc,a[i].c);
	/* cerr<<"a at "<<i<<" "<<_ans<<" now "<<ans.begin()->first<<" + "<<a[i].a<<endl; */
	ins(a[i]);
    }
    cal(0);
	_ans=min(_ans,curb);
	_ans=min(_ans,curc);
    /* cerr<<"a at "<<0<<" "<<_ans<<endl; */
    printf("%d\n",_ans);
}
int main(){
    freopen("checkin.in","r",stdin);
    freopen("checkin.out","w",stdout);
    int T;
    Read(T);
    while(T--)_main();
}
 
