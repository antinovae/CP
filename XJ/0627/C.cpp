#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=101;
int g[maxn];
int n,m;
mt19937 Rnd(114514);
int rnd(){
    return (int)(Rnd()&((1ull<<63)-1));
}
int cal(int S){
    int mx=0;
    vector<int>cur;
    for(int i=0;i<n;i++)if(S>>i&1)cur.push_back(i);
    for(int T=1;T<=10000;T++){
	shuffle(cur.begin(),cur.end(),Rnd);
        int s=0,res=0;
	for(auto u:cur)if((g[u]&s)==s)s|=1ll<<u,++res;
	mx=max(mx,res);
    }
    return mx;
}
signed main(){
    freopen("npc.in","r",stdin);
    freopen("npc.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;i++){
	int x,y;scanf("%lld%lld",&x,&y);
	g[x-1]|=1ll<<(y-1),g[y-1]|=1ll<<(x-1);
    }
    int full=(1ll<<n)-1;
    int S=rnd()&(full),T=full^S;
    int wS=cal(S),wT=cal(T);
    while(wS!=wT){
        if(wS<wT)swap(S,T),swap(wS,wT);
        int x=rnd()%n;
        while(!(S>>x&1))x=rnd()%n;
        T^=1ll<<x,S^=1ll<<x;
        wS=cal(S),wT=cal(T);
    }
    assert(wS==wT);
    printf("%d\n",__builtin_popcountll(S));
    for(int i=0;i<n;i++)if(S>>i&1)printf("%lld ",i+1);
    puts("");
    printf("%d\n",__builtin_popcountll(T));
    for(int i=0;i<n;i++)if(T>>i&1)printf("%lld ",i+1);
    return 0;
}
