#include<bits/stdc++.h>
using namespace std;
const int maxn=1001;
int n,a[maxn][maxn],m;
int vis[maxn][maxn];
int tox[4]={1,-1,0,0};
int toy[4]={0,0,1,-1};
int check(){
    for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
	    if(a[i][j]!=a[1][1])return 0;
	}
    }
    return 1;
}
vector<pair<int,int>>cnt[maxn];
queue<pair<int,int>>q;
vector<pair<int,int>>con;
vector<pair<int,int>>extend(int cur){
    while(!q.empty()){
	const auto [x,y]=q.front();q.pop();
	con.push_back({x,y});
	for(int i=0;i<4;i++){
	    const int nx=x+tox[i],ny=y+toy[i];
	    if(nx<=n&&ny<=n&&nx>=1&&ny>=1){
		if(!vis[nx][ny]){
		    vis[nx][ny]=1;
		    /* cout<<nx<<' '<<ny<<endl; */
		    if(a[nx][ny]==a[x][y])q.push({nx,ny});
		    else {
			cnt[a[nx][ny]].push_back({nx,ny});
		    }
		}
	    }
	}
    }
    /* for(auto [x,y]:con){ */
	/* cout<<x<<' '<<y<<endl; */
    /* } */
    return con;
}
vector<tuple<int,int,int>>ans;
void pr(){
    for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
	    cout<<a[i][j]<<" ";
	}
	cout<<endl;
    }
    cout<<endl;
}
mt19937 rnd(time(0));
void gen(){
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=rnd()%n+1;
}
int main(){
    scanf("%d%d",&n,&m);
    gen();
    /* for(int i=1;i<=n;i++){ */
	/* for(int j=1;j<=n;j++){ */
	    /* scanf("%d",&a[i][j]); */
	/* } */
    /* } */
    const int cur=n/2;
    while(1){
	/* pr(); */
	q.push({cur,cur});
	vis[cur][cur]=1;
	auto res=extend(cur);
	int mx=0;
	for(int i=1;i<=n;i++){
	    if(cnt[i].size()>cnt[mx].size())mx=i;
	    /* cout<<i<<" : "; */
	    /* for(auto v:cnt[i])cout<<v.first<<' '<<v.second<<"   "; */
	    /* cout<<endl; */
	}
	if(mx==0)break;
	for(auto v:cnt[mx]){
	    q.push(v);
	}
	cnt[mx].clear();
	ans.push_back({cur,cur,mx});
	for(const auto &[x,y]:res)a[x][y]=mx;
    }
    ans.push_back({cur,cur,1});
    printf("%zu\n",ans.size());
    for(auto &[x,y,z]:ans){
	printf("%d %d %d\n",x,y,z);
    }
}

