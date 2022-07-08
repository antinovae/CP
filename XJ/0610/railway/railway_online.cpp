#include<bits/stdc++.h>
using namespace std;
const int maxn=100001;
int tot,n,m,Q,dep[maxn],dis[maxn];
pair<int,int> st[18][maxn<<1],p[maxn<<1];
int lg2[maxn<<1];
void st_init(){
    lg2[1]=0;
    for(int i=2;i<=tot;i++){
	lg2[i]=lg2[i>>1]+1;
    }
    for(int i=1;i<=tot;i++)st[0][i]=p[i];
    for(int j=1;j<lg2[tot];j++){
	for(int i=1;i<=tot;i++){
	    if(i+(1<<(j-1))<=tot)st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
	    else st[j][i]={n+1,-1};
	}
    }
}
int pos[maxn];
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
	if(get_dis(x,r)>get_dis(l,r))l=x;
	if(get_dis(x,l)>get_dis(l,r))r=x;
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
vector<pair<int,int>>ins_city[maxn];
vector<int>ins_color[maxn];
struct ans_diam{
    vector<pair<int,int>>bt1,bt2;
    int l,r,nl,nr;//l,r: diff | nl,nr: not strictly diff
    void push(){
	bt1.push_back({l,r});
	bt2.push_back({nl,nr});
    }
    void pop(){
	l=bt1.back().first;
	r=bt1.back().second;
	nl=bt2.back().first;
	nr=bt2.back().second;
    }
    void update(int c){
	int pl=site[c].l,pr=site[c].r;
	if(!nl&&!nr){
	    nl=pl;nr=pr;
	}
	else{
	    if(get_dis(pl,nl)>get_dis(l,r))l=pl,r=nl;
	    if(get_dis(pl,nr)>get_dis(l,r))l=pl,r=nr;
	    if(get_dis(pr,nl)>get_dis(l,r))l=pr,r=nl;
	    if(get_dis(pr,nr)>get_dis(l,r))l=pr,r=nr;
	    if(get_dis(l,r)>get_dis(nl,nr))nl=l,nr=r;
	    if(get_dis(pl,pr)>get_dis(nl,nr))nl=pl,nr=pr;
	}
    }
    int cal(){
	return get_dis(l,r);
    }
}ans;
void solve(int x,int l,int r){
    cout<<"at: "<<x<<"   "<<l<<" "<<r<<endl;
    if(l>r)return;
    if(l==r){
	if(l!=0)printf("%d\n",ans.cal());
	return;
    }
    for(auto [c,v]:ins_city[x]){
	cout<<"insert city: "<<c<<" "<<v<<endl;
	site[c].push();
	site[c].update(v);
    }
    ans.push();
    for(auto c:ins_color[x]){
	cout<<"insert site: "<<c<<endl;
	ans.update(c);
    }
    solve(ls,l,mid);
    solve(rs,mid+1,r);
    for(auto [c,v]:ins_city[x]){
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
int main(){
    scanf("%d%d%d",&n,&m,&Q);
    for(int i=1;i<=n;i++){
	scanf("%d",&c[i].first);
    }
    for(int i=1;i<n;i++){
	int x,y,w;
	scanf("%d%d%d",&x,&y,&w);
	e[x].push_back({y,w});
	e[y].push_back({x,w});
    }
    dfs(1,0);
    st_init();
    for(int i=1;i<=Q;i++){
	int opt;
	scanf("%d",&opt);
	if(opt==1){
	    int u,v;scanf("%d%d",&u,&v);
	    if(c[u].first!=v){
		pair<int,int>cur={u,c[u].first};
		modify_city(1,0,n,c[u].second,i-1,cur);
		if(d[v].first){
		    modify_color(1,0,n,d[v].second,i-1,v);
		    d[v].second=i;
		}
		c[u]={v,i};
	    }
	}
	else{
	    int x;scanf("%d",&x);
	    if(d[x].first){
		modify_color(1,0,n,d[x].second,i-1,x);
		d[x]={0,i};
	    }
	    else d[x]={1,i};
	}
    }
    solve(1,0,n);
}
