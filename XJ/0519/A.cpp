#include<bits/stdc++.h>
using namespace std;
#define int long long
int mo;
const int N=101;
int a[N][N],tmp,d[N][N],p[N][N],ans[N][N];
int n,x,y;
int qpow(int a,int b,int res=1){
    for(;b;b>>=1,a=a*a%mo)if(b&1)res=res*a%mo;
    return res;
}
void solve(int pos){
    for(int i=1;i<=n;i++){
	if(i==pos){
	    for(int j=1;j<=n+1;j++)a[i][j]=0;
	}
	else{
	    int sum=0;
	    for(int j=1;j<=n+1;j++){
		if(j==n+1){
		    (sum+=d[i][j]*p[i][j]%mo)%=mo;
		    a[i][j]=sum*(mo-1)%mo;
		}
		else{
		    if(i!=j){
			if(j!=pos)a[i][j]=p[i][j];
			else a[i][j]=0;
			(sum+=d[i][j]*p[i][j]%mo)%=mo;
		    }
		    else{
			a[i][j]=mo-1;
		    }
		}
	    }
	}
    }
    for(int i=1;i<=n;i++){
	for(int j=i+1;j<=n;j++)
	    if(a[j][i]>a[i][i]){
		swap(a[j],a[i]);
		break;
	    }
	for(int j=1;j<=n;j++){
	    if(j!=i){
		tmp=a[j][i]*qpow(a[i][i],mo-2)%mo;a[j][i]=0;
		for(int k=i+1;k<=n+1;++k)(a[j][k]+=(mo-a[i][k]*tmp%mo)%mo)%=mo;
	    }
	}
    }
    for(int i=1;i<=n;i++)ans[pos][i]=a[i][n+1]*qpow(a[i][i],mo-2)%mo;
}
signed main(){
    freopen("roam.in","r",stdin);
    freopen("roam.out","w",stdout);
    scanf("%lld%lld",&n,&mo);
    for(int i=2;i<=n+1;i++)
	for(int j=1;j<i;j++)
	    scanf("%lld",&d[i][j]),d[j][i]=d[i][j];
    for(int i=2;i<=n+1;i++)
	for(int j=1;j<i;j++)
	    scanf("%lld",&p[i][j]),p[j][i]=p[i][j];
    for(int i=1;i<=n+1;i++){
	int sum=0;
	for(int j=1;j<=n+1;j++){
	    (sum+=p[i][j])%=mo;
	}
	for(int j=1;j<=n+1;j++){
	    p[i][j]=p[i][j]*qpow(sum,mo-2)%mo;
	}
    }
    for(int i=1;i<=n;i++){
	solve(i);
    }
    for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++)printf("%lld ",ans[j][i]);
	puts("");
    }
}
