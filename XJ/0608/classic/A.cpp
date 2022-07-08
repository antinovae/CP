#include<bits/stdc++.h>
using namespace std;
const int maxn=100005,mo=998244353;
int n,a[maxn];
void solve(){
    int ans=0;
    for(int i=0;i<17;i++){
	for(int j=0;j<17;j++){
	    for(int k=0;k<17;k++){
		int b[2][2][2];
		memset(b,0,sizeof(b));
		for(int x=1;x<=n;x++){
		    b[a[x]>>i&1][a[x]>>j&1][a[x]>>k&1]++;
		}
		for(int _i:{0,1})for(int _j:{0,1})for(int _k:{0,1}){
		    for(int __i:{0,1})for(int __j:{0,1})for(int __k:{0,1}){
			ans+=1ll*(1ll<<(i+j+k))%mo*(_i&__i)*(_j|__j)*(_k^__k)*b[_i][_j][_k]%mo*b[__i][__j][__k]%mo;
			ans%=mo;
		    }
		}
	    }
	}
    }
    printf("%d\n",ans);
}
mt19937 rnd(10);
int main(){
    freopen("classic.in","r",stdin);
    freopen("classic.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
	scanf("%d",&a[i]);
    }
    solve();

}
