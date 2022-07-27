
#include <bits/stdc++.h>
using namespace std;
const int maxn=2001;
int n,d,r;
double c[maxn][maxn],f[maxn][maxn];
int main(){
    scanf("%d%d%d",&n,&d,&r);
    for(int i=0;i<=n+d;i++){
	c[i][0]=c[i][i]=1;
	for(int j=1;j<i;j++){
	    c[i][j]=c[i-1][j]+c[i-1][j-1];
	}
    }
    for(int i=1;i<=n;i++){
	for(int j=0;j<=d;j++){
	    for(int k=0;k<=i&&k<=j;k++){
		f[i][j]+=c[i][k]*(f[k][j-k]+min(k,r)*c[j-1][j-k]);
	    }
	}
    }
    printf("%.6lf\n", f[n][d]/c[n+d-1][d]+r);
}
