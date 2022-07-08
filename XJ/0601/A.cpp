#include<bits/stdc++.h>
using namespace std;
const int maxn=101;
int f[maxn][maxn];
int n,mo;
int fac[maxn],inv[maxn];

int qpow(int a,int b,int res=1){
   for(;b;b>>=1,a=a*a%mo)if(b&1)res=res*a%mo;
   return res;
}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    for(int i=0;i<=n;i++)inv[i]=qpow(fac[i],mo-2);
}
int cal(int n,int m){
    return fac[n]*inv[m]%mo*inv[n-m]%mo;
}
int main(){
    scanf("%d%d",&n,&mo);
    init(n);
    f[0][0]=1;
    f[1][1]=1;
    for(int i=2;i<=n;i++){
	for(int j=1;j<=i;j++){
	    for(int k=1;k<=i;k++){
		for(int l=1;l<=j;l++){
		    int vs=f[k-1][l-1];
		    for(int p=1;p*k<=i;p++){
			for(int q=1;q<=p&&q*l<=j&&q<=vs;q++){
			    if(p!=q){
				f[i][j]+=f[i-k][j-l]*cal(vs,q)%mo*qpow((p-q),q)%mo;
			    }
			    else{
				f[i][j]+=f[i-k][j-l]*cal(vs,q)%mo;
			    }
			    cout<<"cur "<<i<<' '<<j<<" max "<<k<<" "<<l<<"  num "<<p<<' '<<q<<"  "<<f[i][j]<<endl;
			}
		    }
		}
	    }
	}
    }
}
