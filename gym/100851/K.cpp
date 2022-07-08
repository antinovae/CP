#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
vector<int>in[maxn],out[maxn];
int nxt[maxn],pre[maxn];
int merge(int x,int y){
    if((nxt[x]&&nxt[x]!=y)||(pre[y]&&pre[y]!=x)){
	cerr<<"Can't Merge"<<endl;
	return 0;

    }
    nxt[x]=y;pre[y]=x;
    return 1;
}
unordered_map<int,int>mp[maxn];
int cc=0,col[maxn];
vector<int>t[maxn];
int dp[1<<20][20],link[20][20];
int n,m;
void print(vector<int> &ans){
    auto p=find(ans.begin(),ans.end(),1);
    rotate(ans.begin(),p,ans.end());
    ans.push_back(1);
    for(auto v:ans){
	printf("%d ",v);
    }
}
int ct[maxn];
int _main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,y;scanf("%d%d",&x,&y);
        in[y].push_back(x),out[x].push_back(y);
	mp[x][y]=1;
    }
    for(int x=1;x<=n;x++){
	if(!in[x].size()||!out[x].size()){
	    cerr<<"isolate point "<<x<<endl;
	    return 0;
	}
	if(in[x].size()==1){
	    if(!merge(in[x][0],x))return 0;
	}
	if(out[x].size()==1){
	    if(!merge(x,out[x][0]))return 0;
	}
    }
    for(int i=1;i<=n;i++){
	if(!pre[i]){
	    int x=i;
	    while(x){
		t[cc].push_back(x);col[x]=cc;x=nxt[x];
	    }
	    ++cc;
	}
    }
    /* cout<<cc<<endl; */
    if(cc==0){
	int x=1,cnt=0;
	vector<int>ans;
	while(cnt<n){
	    ans.push_back(x);
	    x=nxt[x];cnt++;
	}
	for(auto v:ans)ct[v]++;
	for(int i=1;i<=n;i++){
	    if(!ct[i]){
		cerr<<" cc = 0 failed "<<endl;
		return 0;
	    }
	}
	print(ans);
	return 1;
    }
    for(int i=0;i<cc;i++){
	for(int j=0;j<cc;j++){
	    if(mp[t[i].back()][*t[j].begin()])link[i][j]=1;
	}
    }
    /* for(int i=0;i<cc;i++){ */
	/* for(auto v:t[i])cout<<v<<" "; */
	/* cout<<endl; */
    /* } */
    memset(dp,-1,sizeof(dp));
    dp[1<<col[1]][col[1]]=1;
    for(int s=0;s<(1<<cc);s++){
	vector<int>f,g;f.reserve(20),g.reserve(20);
	for(int j=0;j<cc;j++){
	    if(s>>j&1)f.push_back(j);
	    else g.push_back(j);
	}
	for(auto u:f){
	    if(dp[s][u]==-1)continue;
	    /* cout<<"dp: "<<s<<" "<<u<<endl; */
	    for(auto v:g){
		if(link[u][v]){
		    dp[s|(1<<v)][v]=u;
		    /* cout<<u<<" -> "<<v<<endl; */
		}
	    }
	}
    }
    for(int j=0;j<cc;j++){
	if(link[j][col[1]]&&dp[(1<<cc)-1][j]!=-1){
	    int cur=(1<<cc)-1,u=j;
	    vector<int>ans;
	    while(cur){
		reverse(t[u].begin(),t[u].end());
		for(auto v:t[u])ans.push_back(v);
		int v=u;
		u=dp[cur][u];
		cur^=(1<<v);
	    }
	    if(ans.size()!=n)return 0;
	    reverse(ans.begin(),ans.end());
	    print(ans);
	    return 1;
	}
    }
    cerr<<"no result"<<endl;
    return 0;
}
int main(){
    freopen("king.in","r",stdin);
    freopen("king.out","w",stdout);
    if(!_main())puts("There is no route, Karl!");
}
