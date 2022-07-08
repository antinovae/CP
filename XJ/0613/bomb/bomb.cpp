#include"bomb.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=2000010;

#define ref const &

mt19937 rnd(1145140);
int per[maxn];
void create_permutation(int n){
    for(int i=0;i<n;i++)per[i]=i;
    shuffle(per,per+n,rnd);
    /* for(int i=0;i<n;i++)cout<<per[i]<<' ';cout<<endl; */
}
namespace X{
    list<pair<int,int>>s;
    struct my_array{
	vector<int>s;
	int n;
	my_array(vector<int>t){
	    s=t;n=s.size();
	}
	my_array(int x){
	    s.resize(x);
	    n=x;
	}
	int& operator [](int x){
	    return s[(x+n)%n];
	}
    };
}
vector<int>trans(vector<int> ref s){
    vector<int>t(s.size());
    for(int i=0;i<s.size();i++){
	t[i]=s[per[i]];
    }
    return t;
}
vector<int>itrans(const vector<int> &s){
    vector<int>t(s.size());
    for(int i=0;i<s.size();i++){
	t[per[i]]=s[i];
    }
    return t;
}
pair<vector<int>,long long>run_X(int n,int,vector<int> Wire){
    using namespace X;
    create_permutation(n);
    Wire=trans(Wire);
    my_array wire(Wire);
    my_array send(n);
    int start_pos=0;
    int cur=0,pre_start=0;
    for(int i=0;i<n;i++){
	if(!wire[i]){pre_start=i;}
    }
    /* cout<<pre_start<<endl; */
    for(int i=pre_start;i<n+pre_start;i++){
	if(wire[i]==0){
	    cur=0;
	    if(wire[i+1]==0){
		s.push_back({1,i});
	    }
	    else s.push_back({0,i}),send[i]=-1;
	}
	else{
	    cur++;
	    send[i]=-1;
	    if(wire[i+1]==0)s.push_back({-cur,i});
	}
    }
    cur=0;
    pair<int,int>res={n+1,0};
    for(auto [v,pos]:s){
	/* int v=it.first,pos=it.second; */
	/* cout<<v<<" "<<pos<<endl; */
	cur+=v;
	res=min(res,{cur,pos});
    }
    start_pos=(res.second+1)%n;
    /* cout<<start_pos<<endl; */
    while(s.front().second%n!=start_pos){
	s.push_back(s.front());
	s.pop_front();
    }
    for(int i=start_pos;i<start_pos+n;i++){
	while(!s.empty()&&s.front().first>=0)s.pop_front();
	if(send[i]!=-1){
	    if(!s.empty()&&s.front().first==-1){
		/* cout<<"set "<<i<<" 1 "<<s.front().first<<endl; */
		send[i]=1;
		s.pop_front();
	    }
	    else {
		/* cout<<"set "<<i<<" 0 "<<s.front().first<<endl; */
		send[i]=0;
		s.front().first++;
	    }
	}
    }
    return {itrans(send.s),start_pos};
}
vector<int>wire,rev;
int n,m,k,cnt,vis[maxn];
/* int cut_wire(int x){ */
/*     assert(!wire[x]); */
/*     /1* cout<<"cut "<<x<<" "<<rev[x]<<endl; *1/ */
/*     vis[x]=1; */
/*     ++cnt; */
/*     assert(cnt<=n-k); */
/*     return rev[x]; */
/* } */
void run_C(int n,long long start_pos){
    queue<int>q;
    create_permutation(n);
    int cur=0;
    for(int x=start_pos;x<start_pos+n;x++){
	int p=cut_wire(per[(x+n)%n]);
	if(p==0)++cur;
	else if(p==1){
	    q.push(++cur);
	    cur=0;
	}
	else{
	    int step=q.front();q.pop();
	    x+=step;
	}
    }
}
/* int main(){ */
/*     scanf("%d%d",&n,&k); */
/*     wire.resize(n);rev.resize(n); */
/*     for(int i=0;i<k;i++){ */
/* 	wire[i]=1; */
/*     } */
/*     shuffle(wire.begin(),wire.end(),rnd); */
/*     for(int i=0;i<n;i++){ */
/* 	scanf("%d",&wire[i]); */
/* 	cout<<wire[i]<<" "; */
/*     } */
/*     cout<<endl; */
/*     pair<vector<int>,long long> res=run_X(n,m,wire); */
/*     for(auto v:res.first){ */
/* 	cout<<v<<" "; */
/*     } */
/*     cout<<endl; */
/*     cout<<res.second<<endl; */
/*     rev=res.first; */
/*     run_C(n,res.second); */
/*     cout<<cnt<<endl; */
/*     for(int i=0;i<n;i++)cout<<vis[i]<<" "; */
/* } */
