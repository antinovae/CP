#include<bits/stdc++.h>
using namespace std;
int n,m;
const int maxn=100001,INF=1e9;
template<class Tp> struct flow{
    int head[maxn],kl=1,S,T,vis[maxn],dis[maxn];
    struct edge{
	int u,v,nxt;
	Tp w;
    }e[maxn];
    int bfs(){
	memset(vis,0,sizeof(vis));
	memset(dis,0,sizeof(dis));
	queue<int>q;
	while(!q.empty()){
	    int x=q.front();
	    for(int i=head[x];int v=e[i].v;i=e[i].nxt){
		if(!vis[v]&&e[i].w){
		    vis[v]=1;
		    dis[v]=dis[x]+1;
		    if(v==T)return 1;
		    q.push(v);
		}
	    }
	}
	return 0;
    }
    Tp dfs(int x,Tp in){
	if(!in)return 0;
	if(x==T)return in;
	for(int i=head[x];int v=e[i].v;i=e[i].nxt){
	    Tp out=0;
	    if(dis[v]==dis[x]+1&&e[i].w){
		Tp res=dfs(v,min(e[i].w,in));
		e[i].w-=res;e[i^1]+=res;
		in-=res;out+=res;
		if(!in)return out;
	    }
	}
    }
    void sets(int s,int t){
	S=s;T=t;
    }
    void add(int x,int y,Tp c){
	e[++kl]={x,y,head[x],c};head[x]=kl;
	e[++kl]={y,x,head[y],(Tp)0};head[y]=kl;
    }
    Tp push_flow(Tp in){
	Tp ans=(Tp)0;
	while(in&&bfs()){
	    Tp res=dfs(S,in);
	    in-=res;ans+=res;
	}
    }
};
flow<int>F1,F2,F;
flow<double>Fs;
double va,vv;
void trans(flow<int>F1,flow<double>F2){
    for(int i=2;i<=F1.kl;i++){
	if(F1.e[i].w){F2.add(F1.e[i].v,F1.e[i].u,F1.e[i].w);}
    }
}
double ans[maxn][2];

void save(flow<double>F,int p){
    for(int i=2,j=1;i<=F.kl;i+=4){
	if(F.e[i^1].w){
	    ans[j][p]=F.e[i^1].w;
	}
	else if(F.e[(i+2)^1].w){
	    ans[j][p]=-F.e[i^1].w;
	}
    }
}
int main(){
    scanf("%d%d%lf%lf",&n,&m,&va,&vv);
    F1.sets(1,3);
    F2.sets(2,3);
    F.sets(n+1,3);
    F.add(n+1,1,INF);
    F.add(n+1,2,INF);
    for(int i=1;i<=m;i++){
	int x,y,w;
	scanf("%d%d%d",&x,&y,&w);
	F1.add(x,y,w);F1.add(y,x,w);
	F2.add(x,y,w);F2.add(y,x,w);
	F.add(x,y,w);F.add(y,x,w);
    }
    int U1=F1.push_flow(INF);
    int U2=F2.push_flow(INF);
    int U=F.push_flow(INF);
    trans(F,Fs);
    double p=U1*va;
    if(p>=U1)p=U1;
    if(p<=U-U2)p=U-U2;
    Fs.sets(1,3);
    Fs.push_flow(p);
    save(Fs,0);
    Fs.sets(2,3);
    Fs.push_flow(U-p);
    save(Fs,1);
    for(int i=1;i<=m;i++){
	printf("%.10lf %.10lf\n",ans[i][0],ans[i][1]);
    }
}
