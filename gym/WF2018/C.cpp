#include<bits/stdc++.h>

void __my_assert(bool c, int l) {
    if (!c) {
	printf("assertion failed on line %d", l);
	exit(0);
    }
}

#define _my_assert(c, l) __my_assert(c, l)
#define my_assert(c) _my_assert(c, __LINE__)

#define int long long
using namespace std;
const int maxn=1000001,INF=1e12;
int n,x,y,w,dep[maxn];
vector<pair<int,int>>e[maxn];
using pii=pair<int,int>;
struct node{
    pii v;
    int ls,rs,d;
};
int indec;
node t[maxn * 2 + 20];
vector<int>trash;
class heap{
    private:
	int rt;
	int merge(int x,int y){
	    if(!x||!y)return x|y;
	    if(t[x].v>t[y].v)swap(x,y);
	    t[x].rs=merge(t[x].rs,y);
	    if(t[t[x].rs].d>t[t[x].ls].d)swap(t[x].ls,t[x].rs);
	    t[x].d=t[t[x].rs].d+1;
	    my_assert(t[x].d<=20);
	    return x;
	}
    public:
	int empty(){
	    return !rt;
	}
	pair<int,int>top(){
	    my_assert(rt);
	    return t[rt].v;
	}
	void pop(){
	    my_assert(rt);
	    trash.push_back(rt);
	    rt=merge(t[rt].ls,t[rt].rs);
	}
	int new_node(){
	    int x;
	    if(!trash.empty()){
		x=trash.back();
		trash.pop_back();
	    }
	    else x=++indec;
	    return x;
	}
	void push(pii v){
	    int x=new_node();
	    my_assert(v.second);
	    my_assert(indec <= maxn * 2 + 10);
	    t[x]={v,0,0,0};
	    rt=merge(rt,x);
	}
	void join(heap h){
	    rt=merge(rt,h.rt);
	}
}H1[maxn],H2[maxn];
int ans;
int a[maxn],b[maxn];
void solve(int x){
    int d=dep[x],cnt=0;
    while(!H1[x].empty()&&!H2[x].empty()){
	cnt++;
	my_assert(cnt<=2*n);
	auto p=H1[x].top();auto q=H2[x].top();
	if(p.first+q.first-2*d>=0)break;
	H1[x].pop();H2[x].pop();
	int mn=min(p.second,q.second);
	assert(mn);
	p.second-=mn;q.second-=mn;
	ans+=mn*(p.first+q.first-2*d);
	if(p.second)H1[x].push(p);
	if(q.second)H2[x].push(q);
	H1[x].push({2*d-q.first,mn});
	H2[x].push({2*d-p.first,mn});
    }
}
void dfs(int x,int fa){
    for(auto [v,w]:e[x]){
	if(v==fa)continue;
	dep[v]=dep[x]+w;
	dfs(v,x);
	H1[x].join(H1[v]);
	H2[x].join(H2[v]);
    }
    if(a[x])H1[x].push({dep[x],a[x]});
    if(b[x])H2[x].push({dep[x]-INF,b[x]});
    solve(x);
}
signed main(){
    scanf("%lld",&n);
    for(int i=1;i<n;i++){
	scanf("%lld%lld%lld",&x,&y,&w);
	e[x].push_back({y,w});
	e[y].push_back({x,w});
    }
    int m=0;
    for(int i=1;i<=n;i++){
	scanf("%lld%lld",&a[i],&b[i]);
	int mn=min(a[i],b[i]);
	a[i]-=mn,b[i]-=mn,m+=b[i];
    }
    dfs(1,0);
    printf("%lld\n",ans+m*INF);
}
