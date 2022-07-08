#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
int n,m,type,cnt1,cnt2,ans;
struct node{
    int p,t,del;
    friend bool operator < (node a,node b){
        return a.p==b.p?a.t<b.t:a.p<b.p;
    }
}a[N],b[N];
inline void preworks(){
    sort(a+1,a+n+1);
    for(int mn=2e9,i=1;i<=n;++i)
        if(a[i].t>=mn) a[i].del=1; else mn=a[i].t;
    for(int i=1;i<=n;++i) if(!a[i].del) a[++cnt1]=a[i]; n=cnt1;
    sort(b+1,b+m+1);
    for(int mx=-2e9,i=m;i>=1;--i)
        if(b[i].t<=mx) b[i].del=1; else mx=b[i].t;
    for(int i=1;i<=m;++i) if(!b[i].del) b[++cnt2]=b[i]; m=cnt2;
}
void solve(int l1,int r1,int l2,int r2){
    if(l1>r1||l2>r2) return;
    int mid=(l1+r1)/2,id=0,mx=-1e18;
    for(int i=l2;i<=r2;++i)
        if(b[i].t>=a[mid].t||b[i].p>=a[mid].p)
            if((b[i].t-a[mid].t)*(b[i].p-a[mid].p)>mx)
                mx=(b[i].t-a[mid].t)*(b[i].p-a[mid].p),id=i;
    if(id) solve(l1,mid-1,l2,id),solve(mid+1,r1,id,r2),ans=max(ans,mx);
}

signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++)scanf("%lld%lld",&a[i].p,&a[i].t);
    for(int i=1;i<=m;i++)scanf("%lld%lld",&b[i].p,&b[i].t);
    preworks(),solve(1,n,1,m);
    printf("%lld",ans);
    return 0;
}
