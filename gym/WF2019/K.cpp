#include<bits/stdc++.h>
using namespace std;
const int maxn=505;
const int K=2520;
int x[maxn],r[maxn],g[maxn],t[maxn];
int n;
int ok[maxn][maxn];
double f[maxn];
int getmax(int x){
    if(x==2||x==4)return 8;
    else if(x==3)return 9;
    else return x;
}
void solve(int x){
    f[0]++;
    double prd=1; 
    static int ban[maxn][maxn];
    memset(ban,0,sizeof(ban));
    for(int i=1;i<=n;i++){
	int cnt=0,tot=0;
	int d=t[i]/__gcd(K,t[i]);
	int rst=getmax(d),mul=rst/d;
	for(int j=0;j<d;j++){
	    for(int k=0;k<mul;k++){
		if(!ban[rst][j+k*d]){
		    if(ok[i][(j*K+x)%t[i]])++cnt;
		    else ban[rst][j+k*d]=1;
		    tot++;
		}
	    }
	}
	if(tot){
	    prd=1.0*prd*cnt/tot;
	    f[i]+=prd;
	}
	else break;
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
	scanf("%d%d%d",&x[i],&r[i],&g[i]);
	t[i]=r[i]+g[i];
    }
    for(int i=1;i<=n;i++)
	for(int j=r[i];j<r[i]+g[i];j++){
	    int v=(j-x[i]%t[i]+t[i])%t[i];
	    ok[i][v]=1;
	}
    for(int i=0;i<K;i++)solve(i);
    for(int i=0;i<=n;i++)f[i]/=2520;
    for(int i=1;i<=n+1;i++){
	printf("%.10lf\n",f[i-1]-f[i]);
    }
    return 0;
}


