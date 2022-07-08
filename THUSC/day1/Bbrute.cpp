#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=10001;
int n,m,a[maxn],b[maxn];
int solve(int s){
    priority_queue<int>q;
    for(int i=1;i<=m;i++)q.push(b[i]);
    int cur=0,ans=a[1];
    for(int i=s;i<=n;i++){
	if(!q.empty()&&a[i]<q.top()){
	    cur+=q.top();q.pop();q.push(a[i]);
	}
	else cur+=a[i];
	ans=max(ans,cur);
    }
    return ans;
}
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=m;i++)scanf("%lld",&b[i]);
    int ans=a[1];
    for(int i=1;i<=n;i++){
	ans=max(ans,solve(i));
    }
    printf("%lld\n",ans);
}
