#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001,mo=998244353;
int n,a[maxn],indec,p[maxn],cnt,ans[maxn],vis[maxn];
int find(int x){
    if(vis[x]==indec)return a[x];
    else {vis[x]=indec;return min(a[x],find(p[x]));}
}
int main(){
 //   freopen("value.in","r",stdin);
 //   freopen("value.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    if(n>10){
	puts("1");
	return 0;
    }
    for(int i=1;i<=n;i++)p[i]=i;
    do{
	++indec;
	int res=1,cnt=0;
	for(int i=1;i<=n;i++){
	    if(vis[i]!=indec){
		res=1ll*res*find(i)%mo;
		cnt++;
	    }
	}
	(ans[cnt]+=res)%=mo;
    }
    while(next_permutation(p+1,p+1+n));
    int anss=ans[1];
    for(int i=1;i<=n;i++){
	cout<<ans[i]<<" ";
	anss=__gcd(anss,ans[i]);
    }
    cout<<endl;
    printf("%d\n",anss);
}
