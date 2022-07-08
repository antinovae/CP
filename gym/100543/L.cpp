#include<bits/stdc++.h>
using namespace std;
const int maxn=1005;
int n,l[maxn],r[maxn],v[maxn],f[maxn][maxn],vis[maxn][maxn],indec;
vector<int>s;
int solve(int L,int R){
    if(L>R)return 0;
    if(vis[L][R]==indec)return f[L][R];
    vis[L][R]=indec;
    /* cout<<L<<" "<<R<<" "<<f[L][R]<<endl; */
    int lim=-1;
    f[L][R]=1e9;
    for(int i=1;i<=n;i++){
	if(l[i]>=L&&r[i]<=R)
	    lim=max(lim,v[i]);
    }
    if(lim==-1){
	f[L][R]=0;
	return f[L][R];

    }
    for(int i=1;i<=n;i++){
	if(l[i]>=L&&r[i]<=R&&lim==v[i]){
	    for(int j=l[i];j<=r[i];j++){
		f[L][R]=min(f[L][R],solve(L,j-1)+solve(j+1,R)+v[i]);
	    }
	}
    }
    return f[L][R];
}
void _main(){
    ++indec;
    scanf("%d",&n);
    s.resize(0);
    for(int i=1;i<=n;i++){
	scanf("%d%d%d",&l[i],&r[i],&v[i]);
	s.push_back(l[i]);
	s.push_back(r[i]);
    }
    sort(s.begin(),s.end());
    s.erase(unique(s.begin(),s.end()),s.end());
    for(int i=1;i<=n;i++){
	l[i]=lower_bound(s.begin(),s.end(),l[i])-s.begin()+1;
	r[i]=lower_bound(s.begin(),s.end(),r[i])-s.begin()+1;
	/* cout<<l[i]<<" "<<r[i]<<endl; */
    }
    int ans=solve(1,s.size());
    printf("%d\n",ans);
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
	_main();
    }
}
