#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n=30000;
unordered_map<int,int>vis[maxn];
mt19937 rnd(114514);
int dis[maxn][2],ans;
vector<int>e[maxn];
void dfs(int x,int fa){
    for(auto v:e[x]){
	if(v==fa)continue;
	dfs(v,x);
	if(dis[v][0]+1>=dis[x][0])dis[x][1]=dis[x][0],dis[x][0]=dis[v][0]+1;
	else if(dis[v][0]+1>=dis[x][1])dis[x][1]=dis[v][0]+1;
    }
    ans=max(ans,dis[x][0]+dis[x][1]);
}
int fa[maxn];
int find(int x){
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
void make(){
    freopen("in","w",stdout);
    cout<<n<<endl;
    int k=n-1;
    for(int i=1;i<=n;i++)fa[i]=i;
    while(k){
	int x=rnd()%n+1,y=rnd()%n+1;
	if(x==y)continue;
	if(vis[x][y])continue;
	if(find(x)==find(y))continue;
	fa[find(x)]=find(y);
	vis[x][y]=vis[y][x]=1;
	e[x].push_back(y);e[y].push_back(x);
	cout<<x<<" "<<y<<" "<<rnd()%maxn<<endl;
	k--;
    }
    dfs(1,0);
}
int main(){
    make();
}
