#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n,m;
hash<string>hsh;
char s[maxn];
#define ll long long
ll bs=137,mo=998244353;
unordered_map<ll,int>mp;
int indec;
string res[maxn];
int get(ll hsh,const string &s){
    auto p=mp.find(hsh);
    if(p==mp.end()){
	mp[hsh]=++indec;
	res[indec]=s;
	return indec;
    }
    else return mp[hsh];
}
vector<int>e[maxn];
queue<int,list<int>>q;
int vis[maxn];
struct line{
    int id;
    vector<int>cur,ans;
    int oper(){
	while(!cur.empty()){
	    int x=cur.back();cur.pop_back();
	    if(vis[x])continue;
	    else{
		vis[x]=1;
		ans.push_back(x);
		for(auto v:e[x]){
		    if(!vis[v])cur.push_back(v);
		}
		break;
	    }
	}
	return !cur.empty();
    }
}t[30];
void bfs(){
    while(1){
	int p=0;
	for(int i=1;i<=n;i++){
	    p|=t[i].oper();
	}
	if(!p)return;
    }

}
int main(){
    /* freopen("in","r",stdin); */
    scanf("%d%d",&m,&n);
    string s;
    getline(cin,s);
    for(int i=1;i<=n;i++){
	string s;
	getline(cin,s);
	int len=s.size();
	ll hsh=0;
	for(int i=0;i<len;i++)hsh=(hsh*bs+s[i])%mo;
	mp[hsh]=++indec;
	res[indec]=s;
	t[i].cur.push_back(i);
    }
    for(int i=1;i<=m;i++){
	string s;
	getline(cin,s);
	int ps=0;
	ll hsh=0;
	int len=s.size();
	string ss="";
	while(s[ps]!=',')hsh=(hsh*bs+s[ps])%mo,ss+=s[ps],ps++;
	int x=get(hsh,ss);
	/* cout<<ss<<" "<<x<<endl; */
	++ps;
	while(ps<len){
	    hsh=0;
	    string ss="";
	    while(s[ps]!=' '&&ps<len){
		hsh=(hsh*bs+s[ps])%mo,ss+=s[ps],ps++;
	    }
	    int v=get(hsh,ss);
	    /* cout<<x<<" to "<<ss<<" "<<v<<endl; */
	    e[x].push_back(v);
	    ++ps;
	}
    }
    bfs();
    for(int i=1;i<=n;i++){
	string ans="";
	for(auto v:t[i].ans){
	    ans+=res[v];
	    ans+=",";
	}
	ans.pop_back();
	cout<<ans<<endl;
    }
}
