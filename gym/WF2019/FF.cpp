#include<bits/stdc++.h>
using namespace std;
stringstream _cout;
/* #define cout _cout */ 
const int maxn=2000001,INF=1e9+10;
/* vector<int>sx,sy; */
int cur_x;
struct seg{
    int lx,ly,rx,ry;
    void rein(){
	/* lx=lower_bound(sx.begin(),sx.end(),lx)-sx.begin()+1; */
	/* rx=lower_bound(sx.begin(),sx.end(),rx)-sx.begin()+1; */
	/* ly=lower_bound(sy.begin(),sy.end(),ly)-sy.begin()+1; */
	/* ry=lower_bound(sy.begin(),sy.end(),ry)-sy.begin()+1; */
    }
    double cal(){
	return (double)(ry-ly)/(double)(rx-lx)*(cur_x-lx)+ly;
    }
    bool operator < (seg a) {
	return cal()<a.cal();
    }
    void pr(){
	cout<<"Segment "<<lx<<" "<<ly<<" "<<rx<<" "<<ry<<endl;
    }
}l[maxn];
int L,R,n;
struct comp{
    bool operator ()(int x,int y)const {
	return l[x]<l[y];
    }
};
vector<int>c;
int f[maxn];
set<int>s1,s2;
void pr(){
    /* static int s[maxn]; */
    /* for(int i=1;i<=sx.size();i++){ */
	/* cout<<f[i]<<" "; */
	/* s[i]=s[i-1]+f[i]; */
    /* } */
    /* cout<<endl; */
    /* for(int i=1;i<=sx.size();i++){ */
	/* cout<<s[i]<<" "; */
    /* } */
    /* cout<<endl; */
    /* cout<<"pos: ";for(auto v:s1)cout<<v<<" "; */
    /* cout<<"neg: ";for(auto v:s2)cout<<v<<" "; */
    /* cout<<endl; */
    /* cout<<endl; */
}
void del(int x){
    if(f[x]>0)s1.erase(x);
    else if(f[x]<0)s2.erase(x);
}
void ins(int x){
    if(f[x]>0)s1.insert(x);
    else if(f[x]<0)s2.insert(x);
}
void solve(){
    cout<<"LR: "<<L<<" "<<R<<endl;
    f[1]+=INF;
    f[L]-=INF;
    f[R+1]+=INF;
    ins(L);ins(1);ins(R+1);
    for(auto x:c)
	l[x].pr();
    for(auto x:c){
	int l=::l[x].lx,r=::l[x].rx;
	cout<<"round "<<l<<" "<<r<<endl;
	del(l+1); f[l+1]++; ins(l+1);
	del(r); f[r]--; ins(r);
	/* pr(); */
	if(::l[x].ly<::l[x].ry){
	    while(!s1.empty()){
		auto x=s1.lower_bound(l+1);
		if(x==s1.end())break;
		if(*x>=r)break;
		cout<<"push "<<*x<<" "<<f[*x]<<" than "<<l+1<<endl;
		assert(*x>l);
		while(f[*x]&&!s2.empty()){
		    auto v=s2.lower_bound(*x);
		    if(v==s2.end()||*v>=r)break;
		    cout<<*v<<endl;
		    del(*v);
		    assert(f[*v]<0);
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
		/* pr(); */
	    }
	}
	else{
	    l++;r++;
	    pr();
	    while(!s2.empty()){
		auto x=s2.lower_bound(r);
		if(x==s2.begin()||*prev(x)<=l)break;
		x=prev(x);
		cout<<"push "<<*x<<" "<<f[*x]<<" than "<<r<<endl;
		assert(*x<r);
		while(f[*x]&&!s1.empty()){
		    auto nv=s1.lower_bound(*x);
		    if(nv==s1.begin())break;
		    auto v=prev(nv);
		    cout<<*nv<<" "<<*v<<endl;
		    if(*v<=l)break;
		    del(*v);
		    int mn=min(-f[*x],f[*v]);
		    f[*x]+=mn;f[*v]-=mn;
		    ins(*v);
		}
		/* pr(); */
		if(f[*x]){
		    del(l);
		    f[l]+=f[*x];
		    ins(l);
		    f[*x]=0;
		}
		s2.erase(x);
		pr();
	    }
	}
	pr();

    }
}
void sort_seg(){
    static vector<int> e[maxn];
    unordered_map<int,vector<int>>in,out;
    vector<int>s;
    static int deg[maxn];
    for(int i=1;i<=n;i++){
	in[l[i].lx].push_back(i);
	out[l[i].rx+1].push_back(i);
	s.push_back(l[i].lx);
	s.push_back()
	
	l[i].pr();
    }
    set<int,comp>s;
    for(auto i:sx){
    for(int i=1;i<=sx.size();i++){
	cur_x++;
	for(auto v:out[i]){
	    cout<<"del "<<v<<endl;
	    auto it=s.find(v);
	    assert(it!=s.end());
	    s.erase(it);
	}
	for(auto v:in[i]){
	    auto [it,suc]=s.insert(v);
	    cout<<"in "<<*it<<endl;
	    cout<<l[4].cal()<<" "<<l[5].cal()<<endl;
	    assert(suc);
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

	for(auto v:s){
	    cout<<v<<' ';
	}
	cout<<endl;
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
    for(int i=1;i<=n;i++)assert(!deg[i]);
}
int main(){
    scanf("%d%d%d",&L,&R,&n);
    /* sx.push_back(L);sx.push_back(R); */
    /* sx.push_back(INF);sy.push_back(INF); */
    for(int i=1;i<=n;i++){
	int lx,ly,rx,ry;
	scanf("%d%d%d%d",&lx,&ly,&rx,&ry);
	if(lx>rx){
	    swap(lx,rx);swap(ly,ry);
	}
	l[i]={lx,ly,rx,ry};
	/* sx.push_back(lx);sx.push_back(rx); */
	/* sy.push_back(ly);sy.push_back(ry); */
    }
    /* sort(sx.begin(),sx.end()); */
    /* sx.erase(unique(sx.begin(),sx.end()),sx.end()); */
    /* sort(sy.begin(),sy.end()); */
    /* sy.erase(unique(sy.begin(),sy.end()),sy.end()); */
    /* L=lower_bound(sx.begin(),sx.end(),L)-sx.begin()+1; */
    /* R=lower_bound(sx.begin(),sx.end(),R)-sx.begin()+1; */
    for(int i=1;i<=n;i++){
	l[i].rein();
    }
    sort_seg();
    for(auto v:c)cout<<v<<" ";
    /* assert(0); */
    solve();
    int ans=n;
    for(int i=1;i<=sx.size();i++){
	f[i]+=f[i-1];
	cout<<f[i]<<" ";
	if(i>=L&&i<=R)ans=min(ans,f[i]);
    }
    printf("%d\n",ans);
}
