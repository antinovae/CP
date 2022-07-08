#include<bits/stdc++.h>
using namespace std;
int query(int x,int y);
int a[55][1005];
int n,m;
void init(){
    memset(a,0,sizeof(a));
}
int Query(int x,int y){
    if(!a[x][y])a[x][y]=query(x,y);
    return a[x][y];
}
int check(int k){
    int ans=0;
    for(int i=1;i<=n;i++){
	int l=1,r=m,res=0;
	while(l<=r){
	    int mid=(l+r)/2;
	    if(Query(i,mid)<=k)res=mid,l=mid+1;
	    else r=mid-1;
	}
	ans+=res;
    }
    return ans;
}
int INF=1000000000;
void guess(int num_testcase,int n,int m,int K) {
    ::n=n;::m=m;
    init();
    int l=K,r=INF-n*m+K,ans=-1;
    while(l<=r){
	int mid=(l+r)/2;
	if(check(mid)>=K)
	    ans=mid,r=mid-1;
	else l=mid+1;
    }
    for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
	    if (a[i][j]==ans)printf("%d %d %d\n",ans,i,j);
	}
    }
} 
