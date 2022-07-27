#include<bits/stdc++.h>
using namespace std;
const int maxn=1001;
int n,sz[maxn],cur;
const double d=0.9;
double f[2][maxn];
vector<int>e[maxn];
int a[maxn][maxn];
int solve(){
    memset(f[cur^1],0,sizeof(f[1]));
    for(int i=1;i<=n;i++){
	double res=f[cur][i]/sz[i];
	for(auto j:e[i]){
	    f[cur^1][j]+=res;
	}
    }
    double eps=0;
    for(int i=1;i<=n;i++){
	f[cur^1][i]=f[cur^1][i]*d+(1-d)/n;
	eps=max(eps,fabs(f[cur][i]-f[cur^1][i]));
    }
    cur^=1;
    if(eps<1e-6)return 1;
    else return 0;

}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
	    scanf("%d",&a[i][j]);
	    if(a[i][j]){
		e[i].push_back(j);
		sz[i]++;}
	}
	f[0][i]=1.0/n;
    }
    while(!solve());
    for(int i=1;i<=n;i++){
	/* f[cur][i]+=5*1e-7; */
	printf("%.6lf\n",f[cur][i]);
    }
}
