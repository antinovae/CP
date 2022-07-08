#include<bits/stdc++.h>
#define int long long
using namespace	std;
const int maxn=100001;
int n,m;
int a[maxn],b[maxn],id[maxn],sb[maxn];
struct seg{
    int sz,val,sum;
}t[maxn<<2];
#define ls (x<<1)
#define rs (x<<1|1)
int check(int sz,int val){
    if(b[sz]>=val)return 1;
    else return 0;
}
void pushup(int x){
    if(t[rs].sz)t[x].val=t[rs].val;
    else t[x].val=t[ls].val;
    t[x].sz=t[ls].sz+t[rs].sz;
    t[x].sum=t[ls].sum+t[rs].sum;
}
void modify(int x,int l,int r,int d,int v){
    if(l==r){
	t[x].sz=1;t[x].val=t[x].sum=v;
	return;
    }
    int mid=(l+r)/2;
    if(d<=mid){
	modify(ls,l,mid,d,v);
    }
    else modify(rs,mid+1,r,d,v);
    pushup(x);

}
void query(int x,int l,int r,int cur,int sumcur,int &ans){
    if(l==r){
	if(check(t[x].sz+cur,t[x].val)){
	    ans=t[x].sum+sumcur-sb[t[x].sz+cur];
	}
	else{
	    ans=sumcur-sb[cur];
	}
	return;
    }
    int mid=(l+r)/2;
    if(!t[ls].sz||check(t[ls].sz+cur,t[ls].val)){
	query(rs,mid+1,r,cur+t[ls].sz,sumcur+t[ls].sum,ans);
    }
    else{
	query(ls,l,mid,cur,sumcur,ans);
    }
}
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++){
	scanf("%lld",&a[i]);
	id[i]=i;
    }
    for(int i=1;i<=m;i++){
	scanf("%lld",&b[i]);
    }
    sort(b+1,b+1+m,greater<int>());
    for(int i=1;i<=m;i++)sb[i]=sb[i-1]+b[i];
    sort(id+1,id+1+n,[&](int x,int y){return a[x]<a[y];});
    int ans=0;
    for(int i=1;i<=n;i++){
	modify(1,1,n,id[i],a[i]);
	int res=0;
	query(1,1,n,0,0,res);
	ans=max(ans,res);
    }
    printf("%lld\n",ans);
}
