#include <bits/stdc++.h>
const int maxn=1e5+5;
using namespace std;
using int128=__int128; 
int T, n, m;
long long k, a[maxn], b[maxn];
int128 c[maxn];
unsigned long long seed;
long long Get(){
    seed = (seed << 43) ^ (seed >> 15) ^ (seed << 27) ^ seed;
    return seed >> 4;
}
void write(__int128 x){
    if(x >= 10) write(x / 10);
    putchar('0' + x % 10);
}
int128 f(long long x, long long y) {
    return ((((__int128)x * y >> 60) * (x + y) >> 60) * (x >> 30) * (y >> 30) >> 60) * (x + y);
}
struct seg{
    /* int a[M]; */
    int l,r,pos,mid,id,hv;
    int get(){
	pos=(l+r)/2;
	if(l>r){hv=0;return 0;}
	return f(id,pos);
	/* if(!a[pos])a[pos]=query(id,pos); */
	/* return a[pos]; */
    }
}t[maxn];
void init(){
    for(int i=1;i<=n;i++){
	t[i].l=1,t[i].r=m,t[i].id=i,t[i].hv=1;
	t[i].get();
    }
}
int128 solve(int n,int m,int k) {
    ::n=n;::m=m;
    init();
    while(1){
        int a=0,b=0;
        for(int i=1;i<=n;i++)a+=t[i].pos;
        for(int i=1;i<=n;i++)if(t[i].hv)b=b?-1:i;
        if(a==k&&b>0){
	    return t[b].get();
	}
        if(a>k){
            int v=0;
            for(int i=1;i<=n;i++)if(t[i].hv) v=max(v,t[i].get());
            for(int i=1;i<=n;i++)if(t[i].hv && v==t[i].get()){t[i].r=t[i].pos-1,t[i].get();break;}
        }
        else{
            int v=2e9;
	    for(int i=1;i<=n;i++)if(t[i].hv) v=min(v,t[i].get());
	    for(int i=1;i<=n;i++)if(t[i].hv && v==t[i].get()){t[i].l=t[i].pos+1,t[i].get();break;}
	}
    }
}


void solve(){
    cin >> n >> m >> k >> seed;
    for (int i = 1; i <= n; i++) a[i] = Get();
    for (int i = 1; i <= m; i++) b[i] = Get();
    write(solve(n,m,k)); putchar('\n');
}
#include<bits/stdc++.h>
using namespace std;
const int N=51,M=1010;
int query(int x,int y);

int main(){
    cin >> T;
    while(T--) solve();
    return 0;
}

