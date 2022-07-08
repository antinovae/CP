#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,Q;
vector<int> g[maxn];
void init(){
    for(int i=1;i<=n;i++)g[i].push_back(0);
    for(int i=1;i<=n;i++)
	for(int j=i;j<=n;j+=i)
	    g[j].push_back(i);
}
vector<pair<int,int>>q[maxn];
int ans[maxn];
int c[maxn];
void modify(int x,int v){
    for(;x<=n;x+=x&(-x))c[x]+=v;
}
int query(int x,int res=0){
    for(;x;x-=x&(-x))res+=c[x];
    return res;
}
void solve(int p){
    for(int i=p;i<=n;i+=p){
	auto j=lower_bound(g[i].begin(),g[i].end(),p);
	int c=1;
	while(j!=g[i].begin()){
	    auto k=prev(j);
	    modify(*k+1,c);modify(*j+1,-c);
	    c=-c;j=k;
	}
    }
}
int main(){
    scanf("%d%d",&n,&Q);
    init();
    for(int i=1;i<=Q;i++){
	int x,y;scanf("%d%d",&x,&y);
	q[y].push_back({x,i});
    }
    for(int i=1;i<=n;i++){
	solve(i);
	for(auto v:q[i]){
	    ans[v.second]=query(v.first);
	}
    }
    for(int i=1;i<=Q;i++){
	printf("%d\n",ans[i]);
    }
}
