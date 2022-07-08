#include<bits/stdc++.h>
using namespace std;
const int maxn=200005;
int n,a[maxn],f[maxn],c[maxn];
void modify(int x,int v){
    for(;x<=n;x+=x&(-x))c[x]=max(c[x],v);
}
int query(int x,int res=0){
    for(;x;x-=x&(-x))res=max(res,c[x]);
    return res;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
	scanf("%d",&a[i]);
	a[2*n-i+1]=a[i];
    }
    n*=2;
    int ans=0;
    for(int i=1;i<=n;i++){
	f[i]=query(a[i]-1)+1;
	ans=max(ans,f[i]);
	modify(a[i],f[i]);
    }
    printf("%d\n",ans);
}
