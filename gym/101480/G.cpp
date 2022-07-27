#include<bits/stdc++.h>

const int maxn=500001;
using namespace std;
int n,m,a[maxn],sa[maxn],sb[maxn];
struct seg{
    int l,r,h,a,b,cur,alv;
    int pre,nxt;
    void cal(int now){
	h=h+a*(sa[now]-sa[cur])+b*(sb[now]-sb[cur]);
	cur=now;
    }
}t[maxn];
int cal_time(seg A,seg B){
    int t=A.cur,l=t+1,r=m;
    /* cout<<t<<" "<<l<<" "<<r<<endl; */
    /* cout<<A.a<<" "<<A.b<<"   "<<B.a<<" "<<B.b<<endl; */
    /* cout<<"h "<<A.h<<" "<<B.h<<endl; */
    while(l<=r){
	int mid=(l+r)/2;
	int x=sa[mid]-sa[t],y=sb[mid]-sb[t];
	int v=A.h-B.h+(A.a-B.a)*x+(A.b-B.b)*y;
	/* cout<<"rnd "<<mid<<" "<<x<<' '<<y<<" v "<<v<<endl; */
	if(v==0){
	    /* cout<<"return "<<mid<<endl; */
	    return mid;
	}
	else if((v>0)==(A.h>B.h))l=mid+1;
	else r=mid-1;
    }
    return m+1;
}
struct node{
    int t,x,y;
    bool operator < (node a)const {
	if(t!=a.t)return t>a.t;
	else return x>a.x;
    }
};
priority_queue<node>q;
void pr(){
    /* for(int i=1;i<=n;i++){ */
	/* if(t[i].alv)cout<<i<<" time "<<t[i].cur<<" h "<<t[i].h<<" "<<" ab "<<t[i].a<<" "<<t[i].b<<" range "<<t[i].l<<" "<<t[i].r<<" prenxt "<<t[i].pre<<" "<<t[i].nxt<<endl; */
    /* } */
    /* puts(""); */
}
void solve(){
    int cur=0;
    while(!q.empty()){
	auto [now,x,y]=q.top();
	q.pop();
	if(t[y].pre!=x)continue;
	if(now<cur)continue;
	if(!t[x].alv||!t[y].alv)continue;
	int L=t[x].pre,R=t[y].nxt;
	t[x].cal(now);
	t[y].cal(now);
	t[L].cal(now);
	t[R].cal(now);
	if(t[x].h!=t[y].h)continue;

	/* cout<<"round "<<now<<" "<<x<<" "<<y<<endl; */
	pr();
	t[x].r=t[y].r;
	/* cout<<"wawawa "<<t[L].h<<" "<<t[x].h<<" "<<t[y].h<<" "<<t[R].h<<endl; */
	if(L){
	    t[x].a=t[L].h>t[x].h;
	    t[L].b=t[x].h>t[L].h;
	}
	else t[x].a=0;
	if(R<=n){
	    t[x].b=t[R].h>t[x].h;
	    t[R].a=t[x].h>t[R].h;
	}
	else t[x].b=0;
	t[x].pre=L;t[x].nxt=R;
	t[L].nxt=x,t[R].pre=x;
	if(L){
	    if(t[L].h==t[x].h){
		t[L].alv=0;
		t[x].l=t[L].l;
		t[t[L].pre].nxt=x;
		t[x].pre=t[L].pre;
		t[x].a=t[L].a;
	    }
	    else{
		int t1=cal_time(t[L],t[x]);
		/* cout<<"push "<<t1<<"  "<<L<<" "<<x<<endl; */
		if(t1<=m)q.push({t1,L,x});
	    }
	}
	if(R<=n){
	    if(t[R].h==t[x].h){
		t[R].alv=0;
		t[x].r=t[R].r;
		t[t[R].nxt].pre=x;
		t[x].nxt=t[R].nxt;
		t[x].b=t[R].b;
	    }
	    else{
		int t2=cal_time(t[x],t[R]);
		/* cout<<"push "<<t2<<"  "<<x<<" "<<R<<endl; */
		if(t2<=m)q.push({t2,x,R});
	    }
	}
	t[y].alv=0;
        cur=now;
    }
}
char s[maxn];
int main(){
    scanf("%d%d",&n,&m);
    int lst=0;
    for(int i=1;i<=n+1;i++){
	if(i<=n)scanf("%d",&a[i]);
	if(a[i]==a[i-1]);
	else{
	    t[lst].alv=t[i].alv=1;
	    t[lst].nxt=i;
	    t[lst].r=i-1;
	    t[i].h=a[i];
	    t[i].pre=lst;
	    t[i].l=i;
	    t[i].a=t[lst].h>t[i].h;
	    t[lst].b=t[i].h>t[lst].h;
	    lst=i;
	}
    }
    scanf("%s",s+1);
    for(int i=1;i<=m;i++){
	sa[i]=sa[i-1];sb[i]=sb[i-1];
	if(s[i]=='A')sa[i]++;
	else sb[i]++;
    }

    for(int i=1;t[i].nxt<=n;i++){
	int j=t[i].nxt;
	int t1=cal_time(t[i],t[j]);
	/* cout<<i<<" "<<j<<" ans "<<t1<<endl; */
	q.push({t1,i,j});
    }
    solve();
    pr();
    for(int i=1;i<=n;i++){
	if(t[i].alv){
	    t[i].cal(m);
	/* cout<<t[i].h<<" "<<t[i].l<<" "<<t[i].r<<" "<<endl; */
	    for(int j=max(1,t[i].l);j<=min(t[i].r,n);j++){
		printf("%d ",t[i].h);
	    }
	}
    }
    puts("");
}
