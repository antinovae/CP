#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5,INF=1e16;
int n,m,all,w[maxn];
vector<int>e[maxn];
int mn[maxn],dis[maxn],deg[maxn]; 
void dfs(int x){
    mn[x]=INF;
    for(auto v:e[x]){
	dis[v]=dis[x]+w[v];
	dfs(v);
	mn[x]=min(mn[x],mn[v]);
    }
    if(!deg[x])mn[x]=0;
    mn[x]+=w[x];
}
int p[maxn],fa[maxn],res[maxn];
bool cmp(int x,int y){
    return dis[x]<dis[y];
}
string s[maxn];
using pii=pair<int,int>;
priority_queue<pii,vector<pii>,greater<pii>>q;
void solve(){
    for(int i=m+2;i<=all;i++)q.push({mn[i],i});
    for(int i=m+2;i<=all;i++){
	int x=p[i];
	while(!q.empty()&&q.top().first<=dis[x]){
	    int y=q.top().second;q.pop();
	    y=fa[y];deg[y]--;
	    if(!deg[y]&&y!=1)q.push({mn[y],y});
	}
	res[x]=1+q.size();
    }
}
signed main(){
    cin>>n>>m;
    all=n+m+1;
    for(int i=m+2;i<=all;i++){
	int x;cin>>s[i]>>x>>w[i];
	p[i]=i;
	e[x+1].push_back(i);
	fa[i]=x+1;
	deg[x+1]++;
    }
    for(int i=1;i<=m;i++){
	int x;cin>>x>>w[i+1];
	e[x+1].push_back(i+1),fa[i+1]=x+1,deg[x+1]++;
    }
    dfs(1);
    sort(p+m+2,p+all+1,cmp);
    solve();
    for(int i=m+2;i<=all;i++)cout<<s[i]<<' '<<res[i]<<endl;
    return 0;
}
