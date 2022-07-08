#include<bits/stdc++.h>
using namespace std;
const int maxn=1001;
char s[maxn];
int a[maxn][maxn];
int vis[maxn][maxn],n,m,cc,g[maxn][maxn],fa[maxn],cycle[maxn];
int find(int x){
    if(x==fa[x])return x;
    else return fa[x]=find(fa[x]);
}
void merge(int x,int y){
    x=find(x),y=find(y);
    if(x!=y){
	fa[y]=x;
	cycle[x]|=cycle[y];
    }
    else cycle[x]=1;
}
void dfs(int x,int y){
    if(x<=0||x>n)return;
    if(y<=0||y>m)return;
    if(!a[x][y]||vis[x][y])return;
    vis[x][y]=cc;
    dfs(x+1,y);
    dfs(x-1,y);
    dfs(x,y+1);
    dfs(x,y-1);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
	scanf("%s",s+1);
	for(int j=1;j<=m;j++){
	    a[i][j]=s[j]=='.';
	}
    }
    for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
	    if(a[i][j]&&!vis[i][j]){
		++cc;
		dfs(i,j);
	    }
	    cout<<vis[i][j]<<" ";
	}
	cout<<endl;
    }
    for(int i=1;i<=cc;i++)fa[i]=i;
    for(int i=1;i<=m;i++){
	if(a[1][i]&&a[n][i])g[vis[1][i]][vis[n][i]]=1;
    }
    for(int i=1;i<=n;i++){
	if(a[i][1]&&a[i][n])g[vis[i][1]][vis[i][n]]=1;
    }
    for(int i=1;i<=cc;i++){
	for(int j=1;j<=i;j++){
	    if(g[i][j])merge(i,j);
	}
    }
    for(int i=1;i<=cc;i++)fa[i]=find(fa[i]);
    int Q;
    scanf("%d",&Q);
    for(int i=1;i<=Q;i++){
	int x,y;
	scanf("%d%d",&x,&y);
	x=(x%n+n)%n;
	y=(y%m+m)%m;
	x++;y++;
	cout<<x<<" "<<y<<endl;
	int cur=vis[x][y];
	if(cycle[fa[cur]]){
	    puts("yes");
	}
	else puts("no");
    }
}
