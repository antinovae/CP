#include<bits/stdc++.h>
#define int long long
using namespace std;
string ans;
int T=0,R;
int check(int l,int r){
    cout<<"check "<<l<<' '<<r<<endl;
    cin>>ans;
    if(ans=="Yes")return 1;
    else return 0;
}
const int maxn=1000005;
int n;
struct line{
    int k,l,r;
    int cnt(int x,int y){
	if(l>r)return 0;
	int lm=y-k*x;
	if(lm>=l&&lm<=r)return lm-l+1; 
	else if(lm>=l)return r-l+1;
	else return 0;
    }
    void oper(int x,int y,int tp){
	if(l>r)return;
	if(tp==0)r=min(r,y-k*x);
	else{
	    l=max(l,y-k*x+1);
	}
    }
}a[maxn];
int check(int lim){
    int ans=0;
    for(int i=0;i<=n;i++)ans+=a[i].cnt(T,lim);
    return ans;
}
int solve(){
    int m=0;
    for(int i=0;i<=n;i++){
	if(a[i].l<=a[i].r){
	    m+=a[i].r-a[i].l+1;}
	
    }
    if(m==1)return 0;
    int l=0,r=n*T+R,res=0;
    while(l<=r){
	int mid=(l+r)/2;
	if(check(mid)<=m/2)res=mid,l=mid+1;
	else r=mid-1;
    }
    if(check(0,res)){
	for(int i=0;i<=n;i++){
	    a[i].oper(T,res,0);
	}
    }
    else{ 
	for(int i=0;i<=n;i++){
	    a[i].oper(T,res,1);
	}
    }
    return 1;
}
signed main(){
    scanf("%lld%lld",&R,&n);
    for(int i=0;i<=n;i++){
	a[i].k=i;
	a[i].l=0,a[i].r=R;
    }
    while(solve())++T;
    for(int i=0;i<=n;i++){
	if(a[i].r-a[i].l>=0){
	    int res=a[i].k*T+a[i].l;
	    cout<<"answer "<<res<<endl;
	    return 0;
	}
    }
}
