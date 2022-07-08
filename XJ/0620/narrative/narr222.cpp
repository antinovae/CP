#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define maxn 500005
const __int128 one=1;
const __int128 BIG=(one<<100);
using namespace std;
template<typename T> void read(T &num){
    char c=getchar();T f=1;num=0;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){num=(num<<3)+(num<<1)+(c^48);c=getchar();}
    num*=f;
}
template<typename T> void write(T x){
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
int T, n, m;
long long k, a[maxn], b[maxn];
__int128 c[maxn];
unsigned long long seed;
long long Get(){
    seed = (seed << 43) ^ (seed >> 15) ^ (seed << 27) ^ seed;
    return seed >> 4;
}
__int128 f(long long x, long long y) {
    return ((((__int128)x * y >> 60) * (x + y) >> 60) * (x >> 30) * (y >> 30) >> 60) * (x + y);
}
int cl[maxn],cr[maxn],ls[maxn],rs[maxn];
void solve(int l,int r,int L,int R,const __int128 &lim,long long &sum){
    int x=(l+r)/2;
    int cl=max(L,ls[x]),cr=min(R,rs[x]),res=0;
    while(cl<=cr){
	int mid=(cl+cr)/2;
	if(f(a[x],b[mid])<=lim){res=mid;cl=mid+1;}
	else{cr=mid-1;}
    }
    /* cout<<l<<' '<<r<<' '<<x<<" "<<res<<endl; */
    /* assert(res); */
    sum+=res;
    /* if(sum>=k)return; */
    if(l<=x-1)solve(l,x-1,res,R,lim,sum);
    if(x+1<=r)solve(x+1,r,L,res,lim,sum);
    if(sum>=k){
	rs[x]=res;
    }
    else ls[x]=res;
}
long long Cntrk(const __int128 &num){
    /* cout<<"check: "; */
    /* write(num/BIG); */
    /* cout<<endl; */
    long long sum=0;
    solve(1,n,0,m,num,sum);
    /* cout<<"get! "<<sum<<endl; */
    return sum;
}
__int128 work(){
    __int128 ll=f(a[1],b[1]);__int128 rr=0;__int128 ret=0;
    rep(i,1,126)rr=2*rr+1;
    rr=min(rr,f(a[n],b[m]));
    while(ll<=rr){
	__int128 mid=(ll+rr)>>1;
	if(Cntrk(mid)<k){ll=mid+1;}
	else{ret=mid;rr=mid-1;}
    }
    /* cout<<"ok "<<endl; */
    return ret;
}
void solve(){
    read(n);read(m);read(k);read(seed);
    rep(i,1,n)a[i]=Get();
    rep(i,1,m)b[i]=Get();
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
    /* freopen("narrative.in","r",stdin); */
    /* freopen("narrative.out","w",stdout); */
    read(T);
    while(T--)solve();
    return 0;
}

