#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=100005,INF=1e18+maxn;
int n,m,a[maxn],f[maxn],g[maxn],s[maxn];
int check(int h){
    for(int i=1;i<=n;i++)f[i]=0,g[i]=n+1;
    for(int i=1;i<=n;i++){
	int j=h-a[i];
	/* cout<<i<<" "<<i+j<<" "<<i-j<<endl; */
	if(i+j<=n&&i+j>=1)f[i+j]=max(f[i+j],i);
	if(i-j<=n&&i-j>=1)g[i-j]=min(g[i-j],i);
    }
    for(int i=2;i<=n;i++)f[i]=max(f[i],f[i-1]);
    for(int i=n-1;i>=1;i--)g[i]=min(g[i],g[i+1]);
    /* for(int i=1;i<=n;i++){ */
	/* cout<<i<<' '<<f[i]<<" "<<g[i]<<endl; */
    /* } */

    for(int i=1;i<=n;i++){
	if(f[i]<=0||g[i]>=n+1)continue;
	int costl=(i-f[i])*(h-i)+(i+f[i]+1)*(i-f[i])/2-(s[i]-s[f[i]]);
	int costr=(g[i]-(i+1))*(h+i)-((i+1)+g[i]-1)*(g[i]-(i+1))/2-(s[g[i]-1]-s[i]);
	/* cout<<"try "<<i<<" "<<costl<<' '<<costr<<endl; */
	if(costl+costr<=m)return 1;
    }
    /* cout<<"fail"; */
    return 0;
}
signed main(){
    freopen("landscape.in","r",stdin);
    freopen("landscape.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    int L=0,R=INF;
    for(int i=1;i<=n;i++){
	scanf("%lld",&a[i]);
	s[i]=s[i-1]+a[i];
	L=max(a[i],L);
    }
    check(5);
    int res=L;
    while(L<=R){
	int mid=(L+R)/2;
	if(check(mid))res=mid,L=mid+1;
	else R=mid-1;
    }
    printf("%lld\n",res);

}
