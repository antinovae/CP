#include<bits/stdc++.h>
using namespace std;
const int maxn=100001,B=16;
vector<pair<int,int>>e[maxn];
int n,cnt[maxn][B],g[1<<B],f[maxn],dp[1<<B];
void prep(){
    for(int s=1;s<(1<<B);s++){
	/* cout<<"round "<<s<<endl; */
	int st=0;
	for(int i=0;i<B;i++){
	    if(s>>i&1){
		st^=i;
		/* cout<<i<<" "; */
	    }
	}
	/* cout<<endl; */
	if(!((s>>st)&1)){g[s|(1<<st)]=1;}
	/* cout<<"st: "<<st<<" "<<s<<" "<<(s|(1<<st))<<" "<<g[s|(1<<st)]<<endl; */
    }
    for(int s=0;s<(1<<B);s++){
	for(int t=s;t;t=(t-1)&s){
	    dp[s]=max(dp[s],dp[t]+g[s^t]);
	}
    }
}
void pr(int i){
    for(int j=B-1;j>=0;j--)cout<<(i>>j&1);
    cout<<" ";
}
int dfs(int x,int fa,int fw){
    int sum=0;
    for(auto i:e[x]){
	int v=i.first,w=i.second;
	if(v==fa)continue;
	dfs(v,x,w);
	sum^=w;
	f[x]+=f[v];
	for(int i=1;i<B;i++)cnt[x][i]+=cnt[v][i];
    }

    /* cout<<"round "<<x<<" f: "<<f[x]<<endl; */
    /* for(int i=0;i<B;i++){ */
    /* cout<<cnt[x][i]<<' '; */
    /* } */
    /* cout<<endl; */

    for(int i=1;i<B;i++){
	while(cnt[x][i]>=2){
	    cnt[x][i]-=2;
	    f[x]--;
	}
    }
    if(fa&&sum!=fw){
	if(cnt[x][sum^fw]==1){
	    cnt[x][sum^fw]--;
	}
	else{
	    cnt[x][sum^fw]++;
	    f[x]++;
	}
    }
    /* cout<<x<<" sw: "<<sum<<" fw: "<<fw<<" return "<<(sum^fw)<<endl; */
    /* pr(st);cout<<" "<<f[st]<<endl; */
    /* f[x]-=g[st]; */

    return sum^fw;
}
int main(){
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<n;i++){
	int x,y,z;
	scanf("%d%d%d",&x,&y,&z);
	e[x].push_back({y,z});
	e[y].push_back({x,z});
    }
    prep();
    /* for(int i=0;i<(1<<B);i++){ */
	/* cout<<i<<" ";pr(i);cout<<g[i]<<endl; */
    /* } */

    dfs(1,0,0);
    int st=0;
    for(int i=1;i<B;i++){
	st+=((1<<i)*(cnt[1][i]));
    }
    /* cout<<st<<endl; */
    /* cout<<f[1]<<endl; */
    cout<<f[1]-dp[st]<<endl;

}
