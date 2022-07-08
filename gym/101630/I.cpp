#include<bits/stdc++.h>
using namespace std;
const int maxn=100001;
int n;
int type=0;
namespace grader{
    mt19937 rnd(time(0));
    int a[maxn],indec;
    void gen(){
	indec=0;
	vector<int>s0,s1;
	for(int i=1;i<=n;i+=2)s1.push_back(i);
	for(int i=2;i<=n;i+=2)s0.push_back(i);
	shuffle(s0.begin(),s0.end(),rnd);
	shuffle(s1.begin(),s1.end(),rnd);
	for(int i=0;i<n/2;i++){
	    a[++indec]=s1[i];
	    a[++indec]=s0[i];
	}
	if(n&1)a[++indec]=s1.back();
	cerr<<"hidden: ";
	for(int i=1;i<=n;i++)cerr<<a[i]<<" ";cout<<endl;
    }
    int cnt=0;
    int query(int i,int j){
	++cnt;
	return a[i]<a[j];
    }
    void report(vector<int>t){
	for(int i=0;i<n;i++)cerr<<t[i]<<" ";cout<<endl;
	for(int i=1;i<=n;i++){
	    if(a[i]!=t[i-1]){
		puts("WA");
		return;
	    }
	}
	cout<<"AC with step "<<cnt<<endl;
    }
}
unordered_map<int,int>ans[maxn];
int query(int i,int j){
    if(ans[i].find(j)!=ans[i].end())return ans[i][j];
    else{
	if(type==1){
	    /* cout<<"? "<<i<<" "<<j<<endl; */
	    return ans[i][j]=grader::query(i,j);
	}
	else{
	    cout<<"? "<<j/2<<" "<<(i+1)/2<<endl;
	    string s;
	    cin>>s;
	    return ans[i][j]=(s==">");
	}
    }
}
void report(vector<int>ans){
    if(type==1){
	grader::report(ans);
    }
    else{
	cout<<"! ";
	for(auto v:ans){
	    cout<<v<<" ";
	}
	cout<<endl;
    }
}
using group=vector<int>;
vector<int>s;
vector<group*>cur;
group pool[maxn];
int indec;
pair<group*,group*>split(const group *cur,int x){
    group *a=&pool[++indec], *b=&pool[++indec];
    for(auto v:*cur){
	if(!query(x,v))a->push_back(v);
	else b->push_back(v); 
    }
    return {a,b};
}
group *pre[maxn],*nxt[maxn];
void solve(int x){
    auto l=cur.begin(),r=prev(cur.end()),resl=cur.end(),resr=cur.end();
    while(l<=r){
	auto mid=next(l,(r-l)/2);
	if(!query(x,(*mid)->front()))resl=mid,l=next(mid);
	else resr=mid,r=mid-1;
    }
    int fl=1;
    if(resl!=cur.end()){
	auto [p1,p2]=split(*resl,x);
	if(p1->empty()&&p2->empty());
	else if(p1->empty())*resl=p2; 
	else if(p2->empty())*resl=p1; 
	else {
	    pre[x]=p1;
	    nxt[x]=p2;
	    *resl=p2,cur.insert(resl,p1),fl=0;
	}
    }
    if(fl&&resr!=cur.end()){
	auto [p1,p2]=split(*resr,x);
	if(p1->empty()&&p2->empty());
	else if(p1->empty())*resr=p2; 
	else if(p2->empty())*resr=p1; 
	else {
	    pre[x]=p1;
	    nxt[x]=p2;
	    *resr=p2,cur.insert(resr,p1);
	}
    }
}
void pr(){
    /* cerr<<"print: "<<endl; */
    /* for(auto v:cur){ */
	/* cerr<<"    group: "; */
	/* for(auto i:*v){ */
	    /* cerr<<i<<" "; */
	/* } */
	/* cerr<<endl; */
    /* } */
}
signed main(){
    scanf("%d",&n);
    if(n==1){
	cout<<"! 1";
	cout<<endl;
	return 0;
    }
    /* n=5; */
    /* grader::gen(); */
    group *beg=&pool[++indec];
    for(int i=2;i<=n;i+=2){
	beg->push_back(i);
    }
    cur.push_back(beg);
    for(int i=1;i<=n;i+=2){
	solve(i);
	pr();
    }
    vector<int>anss;
    for(auto v:cur){
	assert(v->size()==1);
	anss.push_back(v->front());
    }
    for(int i=1;i<=n;i+=2){
	/* for(auto v:anss)cerr<<v<<" "; cout<<endl; */
	int fl=0;
	for(auto v=anss.begin();v!=anss.end();++v){
	    if(ans[i].find(*v)!=ans[i].end()&&ans[i][*v]==1){
		anss.insert(v,i);
		fl=1;
		break;
	    }
	}
	if(!fl)anss.push_back(i);
    }
    vector<int>ans(n);
    for(int i=0;i<n;i++){
	ans[anss[i]-1]=i+1;
    }
    anss.clear();
    for(int i=1;i<ans.size();i+=2)anss.push_back(ans[i]);
    for(int i=0;i<ans.size();i+=2)anss.push_back(ans[i]);
    report(anss);
}
