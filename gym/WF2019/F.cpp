#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001,INF=2e9+10;
int cur_x;
struct seg{
    int lx,ly,rx,ry;
    double cal(){
	if(cur_x==lx)return ly;
	if(cur_x==rx)return ry;
	return (double)(ry-ly)/(double)(rx-lx)*(cur_x-lx)+ly;
    }
    bool operator < (seg a) {
	return cal()<a.cal();
    }
}l[maxn];
int L,R,n;
struct comp{
    bool operator ()(int x,int y)const {
	return l[x]<l[y];
    }
};
vector<int>c;
map<int,int>f;
set<int>s1,s2;
void del(int x){
    if(f[x]>0)s1.erase(x);
    else if(f[x]<0)s2.erase(x);
}
void ins(int x){
    if(f[x]>0)s1.insert(x);
    else if(f[x]<0)s2.insert(x);
}
void solve(){
    f[-INF]+=INF;
    f[L]-=INF;
    f[R+1]+=INF;
    ins(L);ins(-INF);ins(R+1);
    for(auto x:c){
	int l=::l[x].lx,r=::l[x].rx;
	del(l+1); f[l+1]++; ins(l+1);
	del(r); f[r]--; ins(r);
	if(::l[x].ly<::l[x].ry){
	    while(!s1.empty()){
		auto x=s1.lower_bound(l+1);
		if(x==s1.end()||*x>=r)break;
		while(f[*x]&&!s2.empty()){
		    auto v=s2.lower_bound(*x);
		    if(v==s2.end()||*v>=r)break;
		    del(*v);
		    int mn=min(f[*x],-f[*v]);
		    f[*x]-=mn;f[*v]+=mn;
		    ins(*v);
		}
		if(f[*x]){
		    del(r);
		    f[r]+=f[*x];
		    ins(r);
		    f[*x]=0;
		}
		s1.erase(x);
	    }
	}
	else{
	    l++;r++;
	    while(!s2.empty()){
		auto x=s2.lower_bound(r);
		if(x==s2.begin()||*prev(x)<=l)break;
		x=prev(x);
		while(f[*x]&&!s1.empty()){
		    auto nv=s1.lower_bound(*x);
		    if(nv==s1.begin()||*prev(nv)<=l)break;
		    auto v=prev(nv);
		    del(*v);
		    int mn=min(-f[*x],f[*v]);
		    f[*x]+=mn;f[*v]-=mn;
		    ins(*v);
		}
		if(f[*x]){
		    del(l);
		    f[l]+=f[*x];
		    ins(l);
		    f[*x]=0;
		}
		s2.erase(x);
	    }
	}

    }
}
void sort_seg(){
    static vector<int> e[maxn];
    unordered_map<int,vector<int>>in,out;
    vector<int>b;
    static int deg[maxn];
    for(int i=1;i<=n;i++){
	in[l[i].lx].push_back(i);
	out[l[i].rx].push_back(i);
	b.push_back(l[i].lx);
	b.push_back(l[i].rx);
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());

    set<int,comp>s;
    for(auto i:b){
	cur_x=i;
	for(auto v:in[i]){
	    auto [it,suc]=s.insert(v);
	    if(it!=s.begin()){
		auto l=prev(it);
		e[*l].push_back(*it);
		deg[*it]++;
	    }
	    if(it!=(prev(s.end()))){
		auto r=next(it);
		e[*it].push_back(*r);
		deg[*r]++;
	    }
	}
	for(auto v:out[i]){
	    auto it=s.find(v);
	    s.erase(it);
	}
    }
    vector<int>st;
    for(int i=1;i<=n;i++){
	if(deg[i]==0)st.push_back(i);
    }
    while(!st.empty()){
	int x=st.back();st.pop_back();
	c.push_back(x);
	for(auto v:e[x]){
	    deg[v]--;
	    if(deg[v]==0)st.push_back(v);
	}
    }
}
int main(){
    scanf("%d%d%d",&L,&R,&n);
    for(int i=1;i<=n;i++){
	int lx,ly,rx,ry;
	scanf("%d%d%d%d",&lx,&ly,&rx,&ry);
	if(lx>rx){
	    swap(lx,rx);swap(ly,ry);
	}
	l[i]={lx,ly,rx,ry};
    }
    sort_seg();
    solve();
    int ans=n,pre=0;
    for(auto &v:f){
	pre+=v.second;
	if(v.first>=L&&v.first<=R)ans=min(ans,pre);
    }
    printf("%d\n",ans);
}
