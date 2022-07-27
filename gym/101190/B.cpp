#include<bits/stdc++.h>
using namespace std;
const int maxn=12e6+500;
int n;
int tr[maxn/6][2],tot,indec=1,cr[maxn/12][2];
struct {
    int operator[](int x) const {
	return ((x - 1) ^ 1) + 1;
    }
} iv;
struct {
    struct proxy {
	int u;
	int operator[] (int y) {
	    return u + y + 1;
	}
    };
    auto operator[](int x) const {
	return proxy{x * 6};
    }
} id;
//01: x !x 23: prex pre!x 45: sufx suf!x
vector<int>tag[maxn/6],e[maxn];
void add(int x,int y){
    e[x].push_back(y);
    e[iv[y]].push_back(iv[x]);
}
void insert(string s){
    int n=s.size(),x=1;
    for(int i=0;i<n;i++){
	if(!tr[x][s[i]-'0']){
	    tr[x][s[i]-'0']=++indec;
	}
	x=tr[x][s[i]-'0'];
    }
    if(tag[x].empty())tag[x].push_back(indec);
    else tag[x].push_back(++indec);
}
int beg(int x){
    if(tag[x].empty())return x;
    else return tag[x][0];
}
int ed(int x){
    if(tag[x].empty())return x;
    else return tag[x].back();
}
void dfs(int x){
    for(int i=0;i<tag[x].size();i++){
	int u=tag[x][i];
	add(id[u][3],id[u][1]);
	add(id[u][5],id[u][1]);
	if(i){
	    int v=tag[x][i-1];
	    add(id[u][3],id[v][3]);
	    add(id[v][5],id[u][5]);
	    add(id[u][0],id[v][3]);
	    add(id[v][0],id[u][5]);
	}
	else{
	    add(id[x][1],id[u][5]);
	    add(id[u][5],id[x][1]);
	}
    }
    for(int i:{0,1}){
	int v=tr[x][i];
	if(v){
	    int u=ed(x),w=beg(v);
	    add(id[w][3],id[u][3]);
	    add(id[u][5],id[w][5]);
	    /* add(id[w][0],id[u][3]); */
	    /* add(id[u][0],id[w][5]); */
	}
    }
    for(int i:{0,1}){
	int v=tr[x][i];
	if(v)dfs(v);
    }
}
int dfn[maxn],low[maxn],in[maxn],top,st[maxn],col[maxn],scc;
void tarjan(int x){
    dfn[x]=low[x]=++indec;in[x]=1;st[++top]=x;
    for(auto v:e[x]){
	if(!dfn[v]){
	    tarjan(v);
	    low[x]=min(low[x],low[v]);
	}
	else if(in[v]){
	    low[x]=min(low[x],low[v]);
	}
    }
    if(low[x]==dfn[x]){
	++scc;
	while(st[top]!=x){
	    col[st[top]]=scc;
	    in[st[top]]=0;
	    --top;
	}
	col[x]=scc;
	in[x]=0;
	--top;
    }
}
string s[maxn];
int ans[maxn],pos[maxn];
int main(){
    /* ios::sync_with_stdio(false); */
    /* cin.tie(0); */
    /* cout.tie(0); */
    /* freopen("binary.in","r",stdin); */
    /* freopen("binary.out","w",stdout); */
    cin>>n;
    for(int i=1;i<=n;i++){
	cin>>s[i];
	int m=s[i].size();
	pos[i]=m;
	for(int j=0;j<m;j++)if(s[i][j]=='?')pos[i]=j;
	if(pos[i]<m){
	    s[i][pos[i]]='0';
	    insert(s[i]);
	    int x=indec;
	    s[i][pos[i]]='1';
	    insert(s[i]);
	    int y=indec;
	    cr[i][0]=x;cr[i][1]=y;
	}
	else {
	    insert(s[i]);
	    cr[i][0]=cr[i][1]=indec;
	}
    }
    for(int i=1;i<=indec;i++){
	for(int j=0;j<6;j++)++tot;
    }
    for(int i=1;i<=n;i++){
	int x=cr[i][0],y=cr[i][1];
	if(x==y){
	    add(id[x][1],id[x][0]);
	}
	else{
	    add(id[x][0],id[y][1]);
	    add(id[x][1],id[y][0]);
	}
    }
    indec=0;
    dfs(1);
    for(int i=1;i<=tot;i++){
	if(!dfn[i])tarjan(i);
    }
    for(int i=1;i<=n;i++){
	int x=cr[i][0],y=cr[i][1];
	if(x!=y){
	    if(col[id[x][0]]==col[id[y][0]]){
		cout<<"NO\n";return 0;
	    }
	    else{
		if(col[id[x][0]]<col[id[y][0]])ans[i]=0;
		else ans[i]=1;
	    }
	}
	else {
	    if(col[id[x][0]]==col[id[x][1]]){
		cout<<"NO\n";return 0;
	    }
	}
    }
    cout<<"YES\n";
    for(int i=1;i<=n;i++){
	s[i][pos[i]]=(char)(ans[i]+'0');
	cout<<s[i]<<'\n';
    }
}
