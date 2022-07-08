#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=250001,INF=1e17;
int n,k;
pair<int,int>a[maxn];
int f[maxn][10];
void _main(){
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++){
	scanf("%lld%lld",&a[i].first,&a[i].second);
    }
    sort(a+1,a+n+1);
    for(int j=1;j<=k+1;j++)f[n+1][j]=-INF;
    for(int i=n;i>=1;i--){
	for(int j=k+1;j>=1;j--){
	    if(j==k+1){
		f[i][j]=max(a[i].first-a[i].second,f[i+1][j]);
	    }
	    else{
		f[i][j]=max(f[i+1][j],min(a[i].first-a[i].second,f[i+1][j+1]-a[i].second));
	    }
	}
    }
    printf("%lld\n",max(0ll,f[1][1]));
}
signed main(){
    int T;
    scanf("%lld",&T);
    while(T--){
	_main();
    }
}
