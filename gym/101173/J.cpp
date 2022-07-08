#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5,INF=1e10;
struct edge{
    vector<int>s;
    int a=INF,b=INF,ab=INF,ba=INF,cnta,cntb;
    int solve(){
	/* for(auto v:s){ */
	/*     cout<<v<<" "; */
	/* } */
	/* puts(""); */
	int ans=0;
	a=min(a,ab);
	b=min(b,ba);
	ab=min(ab,a+b);
	ba=min(ba,a+b);
	ab=a+b-ab,ba=a+b-ba;
	/* cout<<a<<" "<<b<<' '<<ab<<" "<<ba<<" "<<endl; */
	for(auto v:s){
	    if(v==0)ans+=a,cnta++;
	    else ans+=b,cntb++;
	}
	int res=0,cnt=0,pr=0;
	if(ab>ba){
	    for(auto v:s){
		if(v==1){
		    if(cnt)--cnt,res+=ab,++pr;
		}
		else cnt++;
	    }
	    res+=(min(cnta,cntb)-pr)*ba;
	}
	else{
	    for(auto v:s){
		if(v==0){
		    if(cnt)--cnt,res+=ba,++pr;
		}
		else cnt++;
	    }
	    res+=(min(cnta,cntb)-pr)*ab;
	}
	/* cout<<"ans: "<<ans-res<<endl; */
	return ans-res;
    }
}G[maxn];
unordered_map<int,int>vis[maxn];
int indec;
int get(int x,int y){
    if(x>y)swap(x,y);
    auto p=vis[x].find(y);
    if(p==vis[x].end()){
	vis[x].insert({y,++indec});
	return indec;
    }
    else return p->second;
}
int a[maxn];
char s[10];
signed main(){
    int n,m;
    scanf("%lld%lld",&n,&n);
    for(int i=1;i<=n;i++){
	scanf("%lld",&a[i]);
    }
    for(int i=2;i<=n;i++){
	int x=a[i-1],y=a[i];
	int id=get(x,y);
	if(x<y)G[id].s.push_back(0);
	else G[id].s.push_back(1);
    }
    scanf("%lld",&m);
    for(int i=1;i<=m;i++){
	int x,y,v;
	scanf("%lld%lld%s%lld",&x,&y,s,&v);
	int id=get(x,y);
	if(s[0]=='O'&&x<y)G[id].a=min(G[id].a,v);
	else if(s[0]=='O'&&x>y)G[id].b=min(G[id].b,v);
	else if(s[0]=='R'&&x<y)G[id].ab=min(G[id].ab,v);
	else if(s[0]=='R'&&x>y)G[id].ba=min(G[id].ba,v);
    }
    int ans=0;
    for(int i=1;i<=indec;i++){
	ans+=G[i].solve();
    }
    printf("%lld",ans);
}
