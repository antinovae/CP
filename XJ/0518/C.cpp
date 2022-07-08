#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=100001;
int n,a[maxn],b[maxn],c[maxn],d[maxn];
int main(){
    freopen("sum.in","r",stdin);
    freopen("sum.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)scanf("%d",&b[i]);
    ll maxx=0;
    int pln=0;
    for(int s=0;s<(1<<n);s++){
	for(int i=1;i<=n;i++){
	    c[i]=a[i],d[i]=b[i];
	    if(s>>(i-1)&1)swap(c[i],d[i]);
	}
	ll ans=0;
	for(int i=1;i<=n;i++){
	    for(int j=1;j<=n;j++){
		ans+=min(c[i],d[j]);
	    }
	}
	if(ans>maxx){
	    maxx=ans;
	    pln=s;
	}
    }
    printf("%lld\n",maxx);
    for(int i=1;i<=n;i++){
	printf("%d ",pln>>(i-1)&1);
    }
    puts("");

}
