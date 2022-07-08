#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=100001;
int tot,n,m,Q,dep[maxn],dis[maxn];
pair<int,int>st[18][maxn<<1],p[maxn<<1];
int lg2[maxn<<1];
void st_init(){
    lg2[1]=0;
    for(int i=2;i<=tot;i++){
	lg2[i]=lg2[i>>1]+1;
    }
    for(int i=1;i<=tot;i++)st[0][i]=p[i];
    for(int j=1;j<=lg2[tot];j++){
	for(int i=1;i<=tot;i++){
	    if(i+(1<<(j-1))<=tot)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	    else st[j][i]=st[j-1][i];
	}
    }
}
int pos[maxn];
int fl;
int get_lca(int x,int y){
    x=pos[x],y=pos[y];
    if(x>y)swap(x,y);
    int len=lg2[y-x+1];
    return min(st[len][x],st[len][y+1-(1<<len)]).second;
}
vector<pair<int,int>>e[maxn];
void dfs(int x,int fa){
    p[++tot]={dep[x],x};
    pos[x]=tot;
    for(auto [v,w]:e[x]){
	if(v==fa)continue;
	dep[v]=dep[x]+1;
	dis[v]=dis[x]+w;
	dfs(v,x);
	p[++tot]={dep[x],x};
    }
}
int get_dis(int x,int y){
    if(x==0||y==0)return 0;
    int z=get_lca(x,y);
    return dis[x]+dis[y]-2*dis[z];
}
struct diam{
    vector<pair<int,int>>bt;
    int l,r;
    void update(int x){
	if(!l&&!r){
	    l=x;
	}
	else{
	    int v1=get_dis(x,r),v2=get_dis(x,l),v=get_dis(l,r),mx=max(max(v1,v2),v);
	    if(mx==v1)l=x;
	    else if(mx==v2)r=x;
	}
    }
    void push(){
	bt.push_back({l,r});
    }
    void pop(){
	if(bt.empty())assert(0);
	l=bt.back().first;
	r=bt.back().second;
	bt.pop_back();
    }
}site[maxn];
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
vector<pair<int,int>>ins_city[maxn<<2];
vector<int>ins_color[maxn<<2];
int col[maxn<<2];
struct ans_diam{
    vector<pair<int,int>>bt1,bt2;
    int l,r,nl,nr;
    void push(){
	bt1.push_back({l,r});
	bt2.push_back({nl,nr});
    }
    void pop(){
	l=bt1.back().first;
	r=bt1.back().second;
	nl=bt2.back().first;
	nr=bt2.back().second;
	bt1.pop_back();bt2.pop_back();
    }
    void update(int c){
	int pl=site[c].l,pr=site[c].r;
	if(!nl&&!nr){
	    nl=pl;nr=pr;
	}
	else{
	    if(!pl&&!pr){}
	    else if(!pl||!pr){
		int p=pl|pr;
		if(col[p]==col[nl]||col[p]==col[nr]){
		    assert(0);

		}
		int v1=get_dis(p,nl),v2=get_dis(p,nr),v=get_dis(l,r),mx=max(max(v1,v2),v);
		if(v1==mx)l=p,r=nl;
		if(v2==mx)l=p,r=nr;
		if(get_dis(l,r)>get_dis(nl,nr))nl=l,nr=r;
	    }
	    else{
		int v1=get_dis(pl,nl),v2=get_dis(pl,nr),v3=get_dis(pr,nl),v4=get_dis(pr,nr),v=get_dis(l,r);
		int mx=max({v,v1,v2,v3,v4});
		if(v1==mx)l=pl,r=nl;
		else if(v2==mx)l=pl,r=nr;
		else if(v3==mx)l=pr,r=nl;
		else if(v4==mx)l=pr,r=nr;
		if(get_dis(l,r)>get_dis(nl,nr))nl=l,nr=r;
		if(get_dis(pl,pr)>get_dis(nl,nr))nl=pl,nr=pr;
	    }
	}
    }
    int cal(){
	return get_dis(l,r);
    }
}ans;
void solve(int x,int l,int r){
    if(l>r)return;
    for(auto [v,c]:ins_city[x]){
	col[v]=c;
	site[c].push();
	site[c].update(v);
    }
    ans.push();
    for(auto c:ins_color[x]){
	ans.update(c);
    }
    if(l==r){
	if(l!=0){
	    printf("%lld\n",ans.cal());
	}
    }
    else{
	solve(ls,l,mid);
	solve(rs,mid+1,r);
    }
    for(auto [v,c]:ins_city[x]){
	site[c].pop();
    }
    ans.pop();
}
void modify_city(int x,int l,int r,int L,int R,const pair<int,int> &v){
    if(l>=L&&r<=R){
	ins_city[x].push_back(v);
	return;
    }
    if(L<=mid)modify_city(ls,l,mid,L,R,v);
    if(R>mid)modify_city(rs,mid+1,r,L,R,v);
}
void modify_color(int x,int l,int r,int L,int R,int v){
    if(l>=L&&r<=R){
	ins_color[x].push_back(v);
	return;
    }
    if(L<=mid)modify_color(ls,l,mid,L,R,v);
    if(R>mid)modify_color(rs,mid+1,r,L,R,v);
}
pair<int,int>c[maxn],d[maxn];
signed main(){
    freopen("railway.in","r",stdin);
    freopen("railway.out","w",stdout);
    scanf("%lld%lld%lld",&n,&m,&Q);
    for(int i=1;i<=n;i++){
	scanf("%lld",&c[i].first);
    }
    for(int i=1;i<=m;i++){
	d[i].first=1;
    }
    for(int i=1;i<n;i++){
	int x,y,w;
	scanf("%lld%lld%lld",&x,&y,&w);
	e[x].push_back({y,w});
	e[y].push_back({x,w});
    }
    dfs(1,0);
    st_init();
    for(int i=1;i<=Q;i++){
	int opt;
	scanf("%lld",&opt);
	if(opt==1){
	    int u,v;scanf("%lld%lld",&u,&v);
		pair<int,int>cur={u,c[u].first};
		modify_city(1,0,Q,c[u].second,i-1,cur);
		if(d[v].first){
		    modify_color(1,0,Q,d[v].second,i-1,v);
		    d[v].second=i;
		}
		if(d[c[u].first].first){
		    int v=c[u].first;
		    modify_color(1,0,Q,d[v].second,i-1,v);
		    d[v].second=i;
	    }
	    c[u]={v,i};
	}
	else{
	    int x;scanf("%lld",&x);
	    if(d[x].first){
		modify_color(1,0,Q,d[x].second,i-1,x);
		d[x]={0,i};
	    }
	    else d[x]={1,i};
	}
    }
    for(int i=1;i<=m;i++){
	if(d[i].first){
	    modify_color(1,0,Q,d[i].second,Q,i);
	    d[i].second=Q+1;
	}
    }
    for(int i=1;i<=n;i++){
	pair<int,int>cur={i,c[i].first};
	modify_city(1,0,Q,c[i].second,Q,cur);
	if(d[i].first&&d[i].second<=Q){
	    modify_color(1,0,Q,d[i].second,Q,i);

	}
    }
    solve(1,0,Q);
}
