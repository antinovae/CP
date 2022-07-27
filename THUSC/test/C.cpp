#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
int n,x,pre[maxn],a[maxn],b[maxn],vis[maxn];
double p[maxn],f[maxn];
int main(){
    int n;
    scanf("%d%d",&n,&x);
    for(int i=1;i<=n;i++){
	scanf("%d%d%lf",&a[i],&pre[i],&p[i]);
    }
    for(int i=1;i<=n;i++){
	if(i==x){
	    int j=i;
	    while(j!=x&&vis[j]!=i){
		vis[j]=i;
		f[i]+=(1/p[i])*a[i];
	    }

	}
	else{

	}
    }
}
