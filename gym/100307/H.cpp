#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn=1e6+5;
int a[maxn],s[maxn],n;
vector<int>pos[maxn];
unordered_map<int,int>mp;
int indec,lst[maxn];
int get(int x){
    auto p=mp.find(x);
    if(p==mp.end()){
	mp[x]=++indec;
	return indec;
    }
    else return p->second;
}
int query(int l,int r,int v){
    int i=get(v);
    auto _l=lower_bound(pos[i].begin(),pos[i].end(),l);
    auto _r=upper_bound(pos[i].begin(),pos[i].end(),r);
    return _r-_l;
}
signed main(){
    freopen("hack.in","r",stdin);
    freopen("hack.out","w",stdout);
    scanf("%lld",&n);
    for(int i=1;i<=n;i++){
	scanf("%lld",&a[i]);
	s[i]=a[i]^s[i-1];
    }
    for(int i=0;i<=n;i++){
	pos[get(s[i])].push_back(i);
    }
    int _and=(1ll<<32)-1;
    long long ans=0;
    for(int i=1;i<=n;i++){
	_and&=a[i];
	for(int k=0;k<32;k++){
	    if(!(a[i]>>k&1))lst[k]=i;
	}
	map<int,int>gap;
	for(int k=0;k<32;k++)gap[lst[k]]|=(1<<k);
	int l=1,cur=_and;
	for(auto [r,w]:gap){
	    ans+=query(l-1,r-1,s[i]^cur);
	    l=r+1;
	    cur|=w;
	}
    }
    printf("%lld\n",ans);
}
