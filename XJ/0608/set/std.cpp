#include<bits/stdc++.h>
using namespace std;
#define PII pair<int,int>
template<class T>inline void chkmin(T &x,T y){if(y<x) x=y;}
template<class T>inline void chkmax(T &x,T y){if(y>x) x=y;}
 
const int N=2e5+5,M=1e6+5,INF=1e9+7;
int n,m;
class heap{
    private:
    public:
	priority_queue<int,vector<int>,greater<int>>del,ins;
	void check(){
	    while(!del.empty()&&del.top()==ins.top())del.pop(),ins.pop();
	    return;
	}
	/* void push(int x){ */
	/*     check(); */
	/*     ins.push(x); */
	/* } */
	/* int top(){ */
	/*     check(); */
	/*     return ins.top(); */
	/* } */
	/* void pop(){ */
	/*     check(); */
	/*     ins.pop(); */
	/* } */
	/* void rmv(int x){ */
	/*     check(); */
	/*     del.push(x); */
	/* } */

}vis[N<<2];
int Mex[N<<2];
void Build(int x,int l,int r){
    Mex[x]=INF;vis[x].ins.push(INF);
    if(l==r) return ;
    int mid=l+r>>1;
    Build(x<<1,l,mid),Build(x<<1|1,mid+1,r);
    return ;
}
void ins(int x,int l,int r,int ql,int qr,int v){
    if(ql<=l&&r<=qr){
        vis[x].ins.push(v);
        Mex[x]=vis[x].ins.top();
        if(l!=r) Mex[x]=min(Mex[x],max(Mex[x<<1],Mex[x<<1|1]));
        return ;
    }
    int mid=l+r>>1;
    if(ql<=mid) ins(x<<1,l,mid,ql,qr,v);
    if(qr>mid) ins(x<<1|1,mid+1,r,ql,qr,v);
    Mex[x]=min(vis[x].ins.top(),max(Mex[x<<1],Mex[x<<1|1]));
    return ;
}
void del(int x,int l,int r,int ql,int qr,int v){
    if(ql<=l&&r<=qr){
        if(vis[x].ins.top()==v) vis[x].ins.pop(),vis[x].check();
        else vis[x].del.push(v);
        Mex[x]=vis[x].ins.top();
        if(l!=r) Mex[x]=min(Mex[x],max(Mex[x<<1],Mex[x<<1|1]));
        return ;
    }
    int mid=l+r>>1;
    if(ql<=mid) del(x<<1,l,mid,ql,qr,v);
    if(qr>mid) del(x<<1|1,mid+1,r,ql,qr,v);
    Mex[x]=min(vis[x].ins.top(),max(Mex[x<<1],Mex[x<<1|1]));
    return ;
}
int query(int x,int l,int r,int ql,int qr){
    // cout<<x<<' '<<l<<' '<<r<<' '<<ql<<' '<<qr<<endl;
    if(ql<=l&&r<=qr) return Mex[x];
    int mid=l+r>>1,res=0;
    if(ql<=mid) res=query(x<<1,l,mid,ql,qr);
    if(qr>mid) chkmax(res,query(x<<1|1,mid+1,r,ql,qr));
    return min(Mex[x],res);
}
set<PII>S[N];
int Ans;
int main(){
    scanf("%d%d",&n,&m);
    vis[1].ins.push(n+1);
    for(int i=1;i<=n;i++){
	vis[1].ins.push(i);
	S[i].insert({n,0});
    }
    Build(1,0,n);Mex[1]=0;
    while(m--){
        int opt,l,r,x;
	scanf("%d%d%d",&opt,&l,&r);
        l^=Ans,r^=Ans;
	if(opt==1){
	    scanf("%d",&x);
	    x^=Ans;
	    cout<<opt<<" "<<l<<" "<<r<<" "<<x<<endl;
	    while(1){
		auto it=S[x].lower_bound({l,0});
		if(it==S[x].end())break;
		if((*it).second>r)break;
		int L=(*it).second,R=(*it).first;
		del(1,0,n,L,R,x),S[x].erase(it);
		if(L<l)ins(1,0,n,L,l-1,x),S[x].insert({l-1,L});
		if(R>r)ins(1,0,n,r+1,R,x),S[x].insert({R,r+1});
	    }
	}
	else{
	    cout<<opt<<" "<<l<<" "<<r<<endl;
	    if(l>r)swap(l,r);
	    Ans=query(1,0,n,l,r);
	    printf("%d\n",Ans);
        }
    }
}
