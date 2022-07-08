#include<bits/stdc++.h>
using namespace std;
#define ls (x<<1)
#define rs (x<<1|1)
const int maxn=200001;
int n,m,son[maxn],f[maxn],cnt[maxn],ans,x,v[maxn];
int to_fa(int x){return cnt[x]<=0?1:-1;}
int from_fa(int x){return cnt[x]>=0?1:-1;}
void upd(int x){
    if(v[x])f[x]=0,son[x]=x;
    else{
        f[x]=1e9,son[x]=0;
        if((ls)<=n&&f[ls]+from_fa(ls)<f[x])f[x]=f[ls]+from_fa(ls),son[x]=son[ls];
        if((rs)<=n&&f[rs]+from_fa(rs)<f[x])f[x]=f[rs]+from_fa(rs),son[x]=son[rs];
    }
}
int main()
{
    freopen("mole.in","r",stdin);
    freopen("mole.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i)scanf("%d",&v[i]);
    for(int i=n;i;--i)upd(i);
    for(int i=1;i<=m;++i){
        scanf("%d",&x);int best=x,minn=f[x];
        for(int t=x,sum=0;t>1;t>>=1){
            sum+=to_fa(t);
            if(f[t>>1]+sum<minn)minn=f[t>>1]+sum,best=t>>1;
        }
        ans+=minn;v[son[best]]--;
        for(int i=x;i>best;i>>=1)--cnt[i],upd(i);
        for(int i=son[best];i>best;i>>=1)++cnt[i],upd(i);
        for(int i=best;i;i>>=1)upd(i);
        printf("%d ",ans);
    }
    return 0;
}
