#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=21;
int n,m,c[2][maxn],f[2][1<<20],K;
bitset<20>a[2][maxn];
vector<int>s[2];
char ch[maxn];
void solve(int n,int p){
    f[p][0]=1;
    s[p].push_back(0);
    for(int i=1;i<(1<<n);i++){
	bitset<20>res;
	int sum=0,ok=1,pc=0;
	for(int j=0;j<n;j++){
	    if(i>>j&1){
		res|=a[p][j],sum+=c[p][j];
		ok&=f[p][i^(1<<j)];
		++pc;
	    }
	}
	f[p][i]=(res.count()>=pc)&ok;
	/* for(int j=0;j<n;j++){ */
	/*     cout<<(i>>j&1); */
	/* } */
	/* cout<<endl; */
	/* cout<<f[p][i]<<"  "<<"cc "<<res.count()<<" pp "<<pc<<" sum "<<sum<<endl; */
	if(f[p][i])s[p].push_back(sum);
    }
}
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=0;i<n;i++){
	scanf("%s",ch);
	for(int j=0;j<m;j++){
	    a[0][i][j]=a[1][j][i]=(ch[j]=='1');
	}
    }
    for(int i=0;i<n;i++)scanf("%lld",&c[0][i]);
    for(int i=0;i<m;i++)scanf("%lld",&c[1][i]);
    scanf("%lld",&K);
    solve(n,0);solve(m,1);
    sort(s[0].begin(),s[0].end());
    sort(s[1].begin(),s[1].end());
    int ans=0;
    /* for(auto v:s[0])cout<<v<<" ";cout<<endl; */
    /* for(auto v:s[1])cout<<v<<" ";cout<<endl; */
    for(auto v:s[0]){
	int p=s[1].end()-lower_bound(s[1].begin(),s[1].end(),K-v);
	ans+=p;
    }
    printf("%lld\n",ans);

}
