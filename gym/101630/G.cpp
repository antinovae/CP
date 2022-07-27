#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=5e5+5,INF=1e16;
int n,m,len,k,a[N],b[N],c[N],sb[N],t[N],sc[N];
void init(){
    scanf("%lld%lld%lld",&n,&len,&k);
    for(int i=1;i<=n;i++)scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&b[i]);
    for(int i=1;i<=n;i++)scanf("%lld",&c[i]);
}
int calcb(int x,int y){
    return sb[y]-sb[x-1];
}

int calcc(int x,int y){
    return sc[y]-sc[x-1];
}
void update(int x,int y){
    while(x<=m){
        t[x]+=y;
	x+=x&(-x);
    }
}

int query(int x){
    int res=0;
    while(x){
        res+=t[x];
        x-=(x&-x);
    }
    return res;
}
int h[N],f[N],g[N];
int isok(int mid){
    memset(t,0,sizeof(t));
    int l,r,j;
    int s;
    int res=0;
    for(int i=len+1;i<=n-len+1;i++){
        l=i-len,r=l+len-1;
        s=calcb(l,r);
        j=lower_bound(h+1,h+m+1,s)-h;
        update(j,1);
        l=i,r=l+len-1;
        s=calcb(l,r);
        j=upper_bound(h+1,h+m+1,mid-s)-h-1;
        res+=query(j);
    }
    memset(t,0,sizeof(t));
    for(int i=1;i<=n-len+1;i++){
        if(i-len>0){
            s=g[i-len];
            j=lower_bound(h+1,h+m+1,s)-h;
            update(j,-1);
        }
        j=upper_bound(h+1,h+m+1,mid-f[i])-h-1;
        res+=query(j);
        s=g[i];
        j=lower_bound(h+1,h+m+1,s)-h;
        update(j,1);
    }
    if(res>=k) return 1;
    return 0;
}
void solve(){
    for(int i=1;i<=n;i++){
        b[i]-=a[i];
        c[i]-=a[i];
        sb[i]=sb[i-1]+b[i];
        sc[i]=sc[i-1]+c[i];
    }
    for(int i=1;i<=n-len+1;i++){
        g[i]=calcc(1,i-1)-calcb(1,i-1)*2+calcc(i,i+len-1)-calcb(i,i+len-1);
        f[i]=calcb(1,i-1)*2-calcc(1,i-1)+calcb(i,i+len-1);
    }
    int s;
    m=0;
    for(int i=len+1;i<=n-len+1;i++){
        int l=i-len,r=l+len-1;
        s=calcb(l,r);
        h[++m]=s;
    }
    for(int i=1;i<=n;i++)h[++m]=g[i];
    h[++m]=INF;
    h[++m]=-INF;
    sort(h+1,h+m+1);
    m=unique(h+1,h+m+1)-h-1;
    int l=0,r=INF,last=0;
    while(l<=r){
        int mid=(l+r)>>1;
        if(isok(mid)){last=mid; r=mid-1;}
	else l=mid+1;
    }
    for(int i=1;i<=n;i++)last+=a[i];
    printf("%lld\n",last);
}
signed main(){
    init();
    solve();
}
