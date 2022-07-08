#include <bits/stdc++.h>
#define maxn 500005
using int128=__uint128_t;
/* const int128 one=1; */
/* const int128 BIG=(one<<100); */
using namespace std;
template<typename T> void write(T x){
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
int T, n, m;
long long k, a[maxn], b[maxn];
int128 c[maxn];
unsigned long long seed;
long long Get(){
    seed = (seed << 43) ^ (seed >> 15) ^ (seed << 27) ^ seed;
    return seed >> 4;
}
int128 f(long long x, long long y) {
    return ((((int128)x * y >> 60) * (x + y) >> 60) * (x >> 30) * (y >> 30) >> 60) * (x + y);
}
int ls[maxn],rs[maxn],res[maxn],vis[maxn];
void solve(int l,int r,int L,int R,const int128 &lim,long long &sum){
    int x=(l+r)/2;
    vis[x]=lim;
    int cl=max(L,ls[x]),cr=min(R,rs[x]),res=0;
    /* cout<<l<<' '<<r<<' '<<x<<" range: "<<cl<<" "<<cr; */
    while(cl<=cr){
	int mid=(cl+cr)/2;
	if(f(a[x],b[mid])<=lim){res=mid;cl=mid+1;}
	else{cr=mid-1;}
    }
    /* cout<<" get "<<res<<endl; */
    /* assert(res); */
    sum+=res;
    ::res[x]=res;
    if(sum>=k)return;
    if(l<=x-1)solve(l,x-1,res,R,lim,sum);
    if(x+1<=r)solve(x+1,r,L,res,lim,sum);
    /* if(sum>=k){ */
	/* rs[x]=res; */
    /* } */
    /* else ls[x]=res; */
}
long long cal(const int128 &num){
    /* cout<<"check: "; */
    /* write(num/BIG); */
    /* cout<<endl; */
    long long sum=0;
    solve(1,n,0,m,num,sum);
    if(sum>=k){
	for(int i=1;i<=n;i++){
	    if(vis[i]==num)rs[i]=min(rs[i],res[i]);
	}
    }
    else{
	for(int i=1;i<=n;i++){
	    if(vis[i]==num)ls[i]=max(ls[i],res[i]);
	}
    }
    /* cout<<"get! "<<sum<<endl; */
    return sum;
}
int128 work(){
    int128 ll=f(a[1],b[1]),rr=f(a[n],b[m]),res=0;
    /* write(ll);puts(""); */
    /* write(rr);puts(""); */
    for(int i=1;i<=n;i++){
	ls[i]=1;rs[i]=m;vis[i]=-1;
    }
    while(ll<=rr){
	int128 mid=(ll+rr)>>1;
	if(cal(mid)<k){
	    ll=mid+1;
	}
	else{res=mid;rr=mid-1;}
    }
    /* cout<<"ok "<<endl; */
    return res;
}
void solve(){
    cin>>n>>m>>k>>seed;
    for(int i=1;i<=n;i++)a[i]=Get();
    for(int i=1;i<=n;i++)b[i]=Get();
    sort(a+1,a+n+1);sort(b+1,b+m+1);
    /* for(int i=1;i<=n;i++){ */
	/* for(int j=1;j<=m;j++){ */
	    /* write(f(a[i],b[j])/BIG);cout<<" "; */
	/* } */
    /*     cout<<endl; */
    /* } */
    write(work());
    puts("");
    return;
}
int main(){
    freopen("narrative.in","r",stdin);
    freopen("narrative.out","w",stdout);
    cin>>T;
    while(T--)solve();
    return 0;
}

