#include<bits/stdc++.h>
using namespace std;
const int maxn=200001;
using graph=vector<pair<int,vector<int>>>;
using queries=vector<tuple<int,int,int>>;
using node=pair<int,vector<int>>;
int n,dis[maxn],ans[maxn],dis1[maxn],dis2[maxn];
vector<int> e[maxn],g[maxn];
void bfs(const graph &cur,int l,int dis[]){
    for(auto [x,edge]:cur)dis[x]=n+1,e[x]=edge;
    dis[l]=0;
    queue<int,list<int>>q;q.push(l);
    while(!q.empty()){
	int x=q.front();q.pop();
	for(auto v:e[x]){
	    if(dis[v]==n+1){
		dis[v]=dis[x]+1;
		q.push(v);
	    }
	}
    }
}
void divide(graph cur,queries qs){
    if(qs.empty())return;
    if(cur.size()<=3){
	for(auto [u,v,id]:qs)ans[id]=(u!=v);
	return;
    }
    int cpos=0,l=0,r=0,mx=cur.size()+1;
    for(auto [x,e]:cur){
	for(auto v:e){
	    if(v<=x)continue;
	    int pos=lower_bound(cur.begin(),cur.end(),(node){v,vector<int>()})-cur.begin();
	    int stp=max(pos-cpos,(int)cur.size()-(pos-cpos));
	    if(stp<=mx)mx=stp,l=x,r=v;
	}
	cpos++;
    }
    graph s1,s2;
    for(auto [x,e]:cur){
	if(x<l||x>r){
	    s1.push_back({x,e});
	}
	else if(x>l&&x<r){
	    s2.push_back({x,e});
	}
	else if(x==l||x==r){
	    vector<int>e1,e2;
	    for(auto v:e){
		if(v==l||v==r)e1.push_back(v),e2.push_back(v);
		else if(v<l||v>r)e1.push_back(v);
		else e2.push_back(v);
	    }
	    s1.push_back({x,e1});
	    s2.push_back({x,e2});
	}
    }
    bfs(cur,l,dis1);
    bfs(cur,r,dis2);
    queries q1,q2;
    for(auto [u,v,id]:qs){
	ans[id]=min(ans[id],dis1[u]+dis1[v]);
	ans[id]=min(ans[id],dis2[u]+dis2[v]);
	ans[id]=min(ans[id],dis1[u]+dis2[v]+1);
	ans[id]=min(ans[id],dis2[u]+dis1[v]+1);
	if((u>l&&u<r)&&(v>l&&v<r))q2.push_back({u,v,id});
	else if((u<l||u>r)&&(v<l||v>r))q1.push_back({u,v,id});
    }
    divide(s1,q1);divide(s2,q2);
}
int main(){
    freopen("distance.in","r",stdin);
    freopen("distance.out","w",stdout);
    scanf("%d",&n);
    graph cur;
    for(int i=1;i<=n-3;i++){
	int x,y;scanf("%d%d",&x,&y);
	g[x].push_back(y);
	g[y].push_back(x);
    }
    for(int i=1;i<n;i++)g[i].push_back(i+1),g[i+1].push_back(i);
    g[1].push_back(n);g[n].push_back(1);
    for(int i=1;i<=n;i++)cur.push_back({i,g[i]});
    int Q;scanf("%d",&Q);
    queries qs;
    for(int i=1;i<=Q;i++){
	int x,y;scanf("%d%d",&x,&y);
	qs.push_back({x,y,i});
	ans[i]=n+1;
    }
    divide(cur,qs);
    for(int i=1;i<=Q;i++){
	printf("%d\n",ans[i]);
    }
}
