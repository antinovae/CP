#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,m;
vector<vector<int>>a;
mt19937 rnd(time(0));
vector<pair<int,int>>ans;
void flip(int x,int y){
    /* cout<<"flip "<<x<<" "<<y<<endl; */
    assert(a[x][y]==0);
    a[x][y]=-1;
    ans.push_back({x,y});
    if(x+1<=n&&a[x+1][y]>=0)a[x+1][y]^=1;
    if(x-1>=1&&a[x-1][y]>=0)a[x-1][y]^=1;
    if(y+1<=m&&a[x][y+1]>=0)a[x][y+1]^=1;
    if(y-1>=1&&a[x][y-1]>=0)a[x][y-1]^=1;
	    /* for(int j=1;j<=n;j++,cout<<endl)for(int k=1;k<=m;k++)cout<<setw(2)<<a[j][k];cout<<endl; */
}
void solve_row(int x){
    /* cout<<"row "<<x<<endl; */
    for(int i=1;i<=m;i++){
	if(a[x][i]==0){
	    flip(x,i);
	    int j=i-1;
	    while(j&&a[x][j]>=0){
		flip(x,j);
		--j;
	    }
	}
    }
}
void solve(){
    static int c[maxn];
    for(int i=1;i<=n;i++){
	int ans=0;
	for(int j=1;j<=m;j++)ans+=a[i][j];
	c[i]=ans&1;
    }
    for(int i=1;i<=n;i++){
	if(c[i]==0){
	    solve_row(i);
	    c[i]=-1;
	    if(c[i+1]>=0)c[i+1]^=1;
	    int j=i-1;
	    while(j&&c[j]>=0){
		c[j]=-1;
		solve_row(j);
		--j;
	    }
	}
    }
    for(auto [x,y]:ans)printf("%d %d\n",x,y);
}
int main(){
    freopen("flip.in","r",stdin);
    freopen("flip.out","w",stdout);
    scanf("%d%d",&n,&m);
    a.resize(n+5);
    for(int i=0;i<n+5;i++)a[i].resize(m+5);
    static char s[maxn];
    int cc=0;
    for(int i=1;i<=n;i++){
	scanf("%s",s+1);
	for(int j=1;j<=m;j++){
	    a[i][j]=(s[j]=='1');
	    cc+=a[i][j];
	}
    }
    if((cc&1)!=((n+m)&1)){
	puts("-1");
	return 0;
    }
    solve();
}
