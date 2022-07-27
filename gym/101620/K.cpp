#include<bits/stdc++.h>
using namespace std;
const int maxn=100001;
int n,ban[maxn],a[maxn],k,b[maxn],m,cnt[8];
string s;
pair<int,int>d[10];
vector<vector<int>>op;
void check(vector<int>cur,int sum){
    if(sum%7!=0)return;
    if(sum==0)return;
    for(auto v:op){
	if(![&]{
	    for(int i=0;i<k;i++){
		if(v[i]>cur[i])return 1;
	    }
	    return 0;
	}())return;
    }
    op.push_back(cur);
}
void dfs(int n,vector<int>cur,int sum){
    if(n>=k){
	check(cur,sum);
	return;
    }
    for(int i=0;i<=min(7,d[n].second);i++){
	cur[n]=i;
	dfs(n+1,cur,sum+i*d[n].first);
    }
}
int main(){
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
	cin>>s;
	if([&]{
	for(int i=0;i<7;i++)
	    if(s[i]!=s[0])return 0;
	    return 1;
	}())ban[i]=1;
	else{
	    pair<string,int> mx={s,0};
	    for(int i=1;i<7;i++){
		s=s.substr(1)+s[0];
		mx=max(mx,{s,i});
	    }
	    b[++n]=mx.second;
	}
    }
    int sum=0,ans=0;
    for(int i=1;i<=n;i++){
	a[i]=(b[i]-b[i-1]+7)%7;
	sum+=a[i];
    }
    a[++n]=7-sum%7;
    for(int i=1;i<=n;i++){
	cnt[a[i]]++;
    }
    for(int i=1;i<=3;i++){
	int res=min(cnt[i],cnt[7-i]);
	ans+=res;cnt[i]-=res;cnt[7-i]-=res;
    }

    for(int i=1;i<7;i++){
	if(cnt[i])d[k++]={i,cnt[i]};
    }
    while(k<3)d[k++]={0,0};
    dfs(0,vector<int>(k),0);
    int f[d[0].second+1][d[1].second+1][d[2].second+1];
    for(int i=0;i<=d[0].second;i++)
	for(int j=0;j<=d[1].second;j++)
	    for(int k=0;k<=d[2].second;k++){
		f[i][j][k]=0;
		if((i*d[0].first+j*d[1].first+k*d[2].first)%7!=0)continue;
		for(auto v:op){
		    if(i-v[0]>=0&&j-v[1]>=0&&k-v[2]>=0)f[i][j][k]=max(f[i][j][k],f[i-v[0]][j-v[1]][k-v[2]]+1);
		}
	    }
    ans+=d[0].second+d[1].second+d[2].second-f[d[0].second][d[1].second][d[2].second];
    printf("%d\n",ans);

}
