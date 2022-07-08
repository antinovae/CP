#include<bits/stdc++.h>
using namespace std;
#define int long long
struct node{
    int x,tp;bool c;
};
vector<node>t;
signed main(){
    freopen("segment.in","r",stdin);
    freopen("segment.out","w",stdout);
    int n,m,C;
    scanf("%lld%lld%lld",&n,&m,&C);
    for(int i=1;i<=n;i++){
	int x,y;scanf("%lld%lld",&x,&y);
	t.push_back({x,0,true});
	t.push_back({y,0,false});
    }
    for(int i=1;i<=m;i++){
	int x,y;scanf("%lld%lld",&x,&y);
	t.push_back({x,1,true});
	t.push_back({y,1,false});
    }
    sort(t.begin(),t.end(),[&](node a,node b){
	    if(a.x==b.x) return (a.c<b.c);
	    return (a.x<b.x);
	    });
    assert(!t.empty());
    int s0=0,s1=0;ZZ
    bool c0=false,c1=false;
    /* for(auto [x,y,z]:t){ */
	/* cout<<x<<" "<<y<<" "<<z<<endl; */
    /* } */
    for(int i=0;i<t.size()-1;i++){
	while(i<t.size()-1&&t[i].x==t[i+1].x){
	    /* cout<<"ins "<<i<<endl; */
	    if(t[i].tp==0)c0=t[i].c;
	    else c1=t[i].c;
	    ++i;
	}
	/* cout<<"ins "<<i<<endl; */
	if(t[i].tp==0)c0=t[i].c;
	else c1=t[i].c;
	int len=t[i+1].x-t[i].x;
	/* cout<<"cur "<<i<<" len "<<len<<endl; */
	/* cout<<c0<<' '<<c1<<endl; */
	/* cout<<s0<<" "<<s1<<endl; */
	if(c0&&c1){
	    if(max(s0,s1)-min(s0,s1)<=C){
		s0+=2*len;
		s1+=2*len;
	    }
	    else if(s1>s0+C){
		s1=s0+C+2*len;
		s0+=2*len;
	    }
	    else if(s0>s1+C){
		int t1=s1+C+2*len,t2=s0+len;
		if(t1>t2)s0=t1,s1+=2*len;
		else s0=t2,s1+=len;
	    }
	    else assert(0); 
	}
	else if(c0)s0+=len;
	else if(c1)s1+=len;
    }
    printf("%lld\n",s0);
    return 0;
} 
