#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=j;i<=k;i++)
#define maxn 500005
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
void solve(int l,int r,int L,int R){
    int x=(l+r)/2,cl=1,cr=m;

}
long long Cntrk(__int128 num){
    long long ans=0;int R=0;
    int l=1;int r=m;
    while(l<=r){
	int mid=(l+r)>>1;
	if(f(a[1],b[mid])<=num){R=mid;l=mid+1;}
	else{r=mid-1;}
    }
    ans+=R;
    rep(i,2,n){
	while(R&&f(a[i],b[R])>num)R--;
	ans+=R;
	if(ans+1ll*(n-i)*R<k)return ans;
	if(ans>k)return ans;
    }
    return ans;
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
    return ret;
}
void solve(){
    read(n);read(m);read(k);read(seed);
    rep(i,1,n)a[i]=Get();
    rep(i,1,m)b[i]=Get();
    sort(a+1,a+n+1);sort(b+1,b+m+1);
    write(work());
    return;
}
int main(){
    /* freopen("narrative.in","r",stdin); */
    /* freopen("narrative.out","w",stdout); */
    read(T);
    while(T--)solve();
    return 0;
}

