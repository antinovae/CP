#include<bits/stdc++.h>
using namespace std;
stringstream _cout;
#define cout _cout
const int maxn=1000001;
vector<int>e[maxn];
struct graph{int l,r;};
int indec=0,fa[maxn];
int new_node(){
    ++indec;
    fa[indec]=indec;
    return indec;
}
int find(int x){
    return(x==fa[x])?x:fa[x]=find(fa[x]);
}
void merge(int x,int y){
    x=find(x),y=find(y);
    if(x==y)assert(0);
    fa[y]=x;
}
class env{
    private:
	unordered_map<string,int>binds;
    public:
	int cal(string name){
	    if(binds.find(name)!=binds.end())return binds.find(name)->second;
	    else assert(0);
	}
	void insert_bind(string name,int val=0){
	    if(binds.find(name)!=binds.end())assert(0);
	    else binds.insert({name,val});
	}
	void modify_bind(string name,int val){
	    if(binds.find(name)==binds.end())assert(0);
	    else binds[name]=val;
	}
	void remove_bind(string name){
	    if(binds.find(name)==binds.end())assert(0);
	    else binds.erase(name);
	}
};
class expr{
    public:
	virtual any eval(env &cur_env)=0;
	virtual void print(int tabs)=0;
	virtual string type_name()=0;
	virtual ~expr() = default;
};
graph C(const vector<any> &s);
graph loop(const vector<any> &s);
graph T(const vector<any> &s);
class number;
class func:public expr{
    private:
	string name;
	vector<shared_ptr<expr>>paras;
    public:
	template <class A, class B>
	func(A &&name, B &&paras) : name(std::forward<A>(name)), paras(std::forward<B>(paras)) {}
	func(string name):name(name){}
	any eval(env &cur_env){
	    cout<<"FUNCTION: "<<name<<": "<<endl;
	    vector<any>_paras;
	    if(paras.size()==2&&(paras[0]->type_name()=="number"||paras[0]->type_name()=="variable")){
		cout<<"identified"<<endl;
		any p=paras[0]->eval(cur_env);
		if(p.type()==typeid(int)){
		    for(int i=1;i<=any_cast<int>(p);i++){
			_paras.push_back(paras[1]->eval(cur_env));
		    }
		    if(name=="c")return C(_paras);
		    else if(name=="loop")return loop(_paras);
		    else if(name=="t")return T(_paras);
		    else assert(0);
		}
	    }

	    for(auto &v:paras){
		any p=v->eval(cur_env);
		if(p.type()==typeid(vector<any>))
		    for(auto v:any_cast<vector<any>>(p))_paras.push_back(v);
		else _paras.push_back(p);
	    }
	    if(name=="c"){
		return C(_paras);
	    }
	    else if(name=="loop"){
		return loop(_paras);
	    }
	    else if(name=="t"){
		return T(_paras);
	    }
	    else assert(0);
	}
	void print(int tabs){
	    for(int i=0;i<tabs;i++)cout<<"  ";
	    cout<<"FUNCTION: "<<name<<": "<<endl;
	    for(auto v:paras){
		v->print(tabs+1);
	    }
	    cout<<endl;
	}
	string type_name(){
	    return "function";
	}
};
class range:public expr{
    private:
	string name;
	shared_ptr<expr>l,r;
	shared_ptr<expr> body;
    public:
	template <class L,class R,class T>
	range(string name,L l,R r,T &&body):name(name),l(l),r(r),body(std::forward<T>(body)){};
	any eval(env &cur_env){
	    cout<<"RANGE: "<<name<<": "<<endl;
	    vector<any>res;
	    cur_env.insert_bind(name);
	    int _l=any_cast<int>(l->eval(cur_env)),_r=any_cast<int>(r->eval(cur_env));
	    if(_l>_r)swap(_l,_r);
	    for(int i=_l;i<=_r;i++){
		cur_env.modify_bind(name,i);
		cout<<name<<" = "<<i<<endl;
		res.push_back(body->eval(cur_env));
	    }
	    cur_env.remove_bind(name);
	    return res;
	}
	void print(int tabs){
	    for(int i=0;i<tabs;i++)cout<<"  ";
	    cout<<"RANGE: "<<name<<": "<<endl;
	    l->print(tabs+1);
	    r->print(tabs+1);
	    body->print(tabs+1);
	    cout<<endl;
	}
	string type_name(){
	    return "range";
	}
};
class variable:public expr{
    private:
	string s;
    public:
	variable(string _s){s=_s;}
	any eval(env &cur_env){
	    /* cout<<s<<endl; */
	    return cur_env.cal(s);
	}
	void print(int tabs){
	    for(int i=0;i<tabs;i++)cout<<"  ";
	    cout<<s<<endl;

	}
	string type_name(){
	    return "variable";
	}
};
class number:public expr{
    private:
	int v;
    public:
	number(int v):v(v){}
	any eval(env &cur_env){
	    /* cout<<v<<endl; */
	    return v;}
	void print(int tabs){
	    for(int i=0;i<tabs;i++)cout<<"  ";
	    cout<<v<<endl;
	}
	string type_name(){
	    return "number";
	}
};
void add_edge(int x,int y){
    cout<<"addedge "<<x<<' '<<y<<endl;
    e[x].push_back(y);e[y].push_back(x);
}
graph C(int x){
    cout<<"call c "<<x<<endl;
    int l=new_node();
    for(int i=1;i<=x;i++){
	int p=indec;
	add_edge(p,new_node());
    }
    return {l,indec};
}
graph C(){return C(1);}
graph C(const vector<graph> &s){
    cout<<"call c graph"<<endl;
    for(int i=0;i<s.size()-1;i++){
	merge(s[i].r,s[i+1].l);
    }
    return {s[0].l,s.back().r};
}
graph C(const vector<any> &s){
    if(s.empty())return C();
    if(s[0].type()==typeid(int)){
	return C(any_cast<int>(s[0]));
    }
    else{
	vector<graph>t;
	for(auto &v:s)t.push_back(any_cast<graph>(v));
	return C(t);
    }
}
graph loop(const vector<graph> &s){
    auto [l,r]=C(s);
    merge(l,r);
    return *s.begin(); 
}
graph loop(int x){
    auto [l,r]=C(x);
    merge(l,r);
    return {l,l+1};
}
graph loop(const vector<any> &s){
    if(s.size()==1&&s[0].type()==typeid(int))return loop(any_cast<int>(s[0]));
    else{
	vector<graph>t;
	for(auto &v:s)t.push_back(any_cast<graph>(v));
	return loop(t);
    }
}
graph T(int x){
    cout<<"call T "<<x<<endl;
    int l=new_node();
    for(int i=1;i<=x;i++){
	add_edge(l,new_node());
    }
    return {l,l+1};
}
graph T(const vector<graph> &s){
    cout<<"call T graph";
    int cur=0;
    for(auto &v:s){
	if(!cur)cur=v.l;
	else merge(cur,v.l);
    }
    return {cur,s.begin()->r};
}
graph T(const vector<any> &s){
    if(s.size()==1&&s[0].type()==typeid(int))return T(any_cast<int>(s[0]));
    else{
	vector<graph>t;
	for(auto &v:s)t.push_back(any_cast<graph>(v));
	return T(t);
    }
}
using iter = string::iterator;
any read_symbol(string &s,iter &p){
    while(p!=s.end()&&(*p==','))++p;
    if(*p<='9'&&*p>='0'){
	int res=0;
	while(p!=s.end()&&*p<='9'&&*p>='0')res=res*10+(*p-'0'),++p;
	return res;
    }
    else if(*p>='A'&&*p<='Z'){
	string res;
	res+=*p;++p;
	return res;
    }
    else{
	string res;
	while(*p>='a'&&*p<='z')res+=*p,++p;
	return res;
    }
}
tuple<string,shared_ptr<expr>,shared_ptr<expr>>read_range_para(string &s,iter &p){
    string name=any_cast<string>(read_symbol(s,p));
    
    any l=read_symbol(s,p);
    shared_ptr<expr> _l;
    if(l.type()==typeid(int)){_l=make_shared<number>(any_cast<int>(l)); }
    else{_l=make_shared<variable>(any_cast<string>(l)); }

    any r=read_symbol(s,p);
    shared_ptr<expr> _r;
    if(r.type()==typeid(int)){ _r=make_shared<number>(any_cast<int>(r)); }
    else{_r=make_shared<variable>(any_cast<string>(r)); }
    ++p;
    return {name,_l,_r};
}
shared_ptr<expr> read_statement(string &s,iter &p){ 
    while(p!=s.end()&&(*p==','))++p;
    cout<<"at: "<<p-s.begin()<<" "<<s.substr(p-s.begin())<<endl;
    any res=read_symbol(s,p);
    if(res.type()==typeid(int)){
	cout<<"find_int "<<any_cast<int>(res)<<endl;
	return make_shared<number>(any_cast<int>(res));
    }
    else if(res.type()==typeid(string)){
	string type=any_cast<string>(res);
	if(type.size()==0)assert(0);
	if(type=="range"){
	    ++p;
	    auto [name,l,r]=read_range_para(s,p);
	    shared_ptr<expr>body;
	    if(*p!=')')body=read_statement(s,p);
	    else body=make_shared<func>("c");
	    cout<<"find_range "<<name<<endl;
	    auto rng=make_shared<range>(name,l,r,body);
	    return rng;
	}
	else if(type.size()==1&&*type.begin()<='Z'&&*type.begin()>='A'){
	    auto var=make_shared<variable>(type);
	    return var;
	}
	else{
	    cout<<"find_function "<<any_cast<string>(res)<<endl;
	    vector<shared_ptr<expr>>para;
	    if(*p=='('){
		while(p!=s.end()&&*p!=')'){
		    ++p;
		    para.push_back(read_statement(s,p));
		    cout<<"find para "<<p-s.begin()<<" "<<s.substr(p-s.begin())<<endl;
		}
		++p;
	    }
	    auto fun = std::make_shared<func>(any_cast<string>(res),para);
	    return fun;
	}
    }
    else assert(0);
}
vector<pair<int,int>>g[maxn];
int tot=0,id[maxn],pos[maxn],kl;
void rebuild(int l,int r){
    for(int i=1;i<=indec;i++){
	cout<<i<<" "<<find(i)<<"   ";
	for(int  v:e[i])cout<<v<<' ';
	cout<<endl;
    }
    for(int i=1;i<=indec;i++)find(i);
    for(int i=1;i<=indec;i++){
	if(i==fa[i])id[i]=++tot,pos[tot]=i;
    }
    if(id[fa[l]]!=1)swap(id[fa[l]],id[pos[1]]);
    if(id[fa[r]]!=tot)swap(id[fa[r]],id[pos[tot]]);
    for(int i=1;i<=indec;i++){
	for(auto v:e[i]){
	    if(i<v){
		g[id[find(i)]].push_back({id[find(v)],++kl});
		g[id[find(v)]].push_back({id[find(i)],kl});
	    }
	}
    }
    for(int i=1;i<=tot;i++){
	for(auto [v,w]:g[i])if(i<v)cout<<i<<' '<<v<<endl;
    }
}

int vis[maxn],tg[maxn],st[maxn],top;
void dfs(int x){
    for(auto [v,w]:g[x]){
	if(vis[w])continue;
	vis[w]=1;
	dfs(v);
	st[++top]=v;
    }
}
void euler(){
    vector<int>s;
    for(int i=1;i<=tot;i++){
	if(g[i].size()&1)s.push_back(i);
    }
    for(int i=0;i<s.size();i+=2){
	g[s[i]].push_back({s[i+1],++kl});
	g[s[i+1]].push_back({s[i],kl});
	tg[s[i]]=s[i+1];tg[s[i+1]]=s[i];
    }
    if(s.size())dfs(s[0]);
    else dfs(1);
    for(int i=1;i<=top;i++)cout<<st[i]<<" ";cout<<endl;
    /* reverse(st+1,st+1+top); */
    /* rotate(st+1,find(st+1,st+1+top,s[0]),st+1+top); */
    /* if(g[st[1]]!=st[2]); */
    if(s.size()){
    for(int i=1;i<top;i++){
	if(tg[st[i]]==st[i+1]){
	    /* cout<<st[i]<<" "<<st[i+1]<<endl; */
	    tg[st[i]]=tg[st[i+1]]=0;
	    rotate(st+1,st+i+1,st+1+top);
	    break;
	}
    }
    }
    else st[++top]=st[1];
    /* for(int i=1;i<=top;i++)cout<<st[i]<<" ";cout<<endl; */
    vector<vector<int>>ans(1);
    ans.back().push_back(st[1]);
    for(int i=2;i<=top;i++){
	if(tg[st[i]]==st[i-1]){
	    tg[st[i]]=0;tg[st[i-1]]=0;
	    ans.push_back(vector<int>());
	}
	ans.back().push_back(st[i]);
    }
    cout<<endl;
    printf("%d %zu\n",tot,ans.size());
    for(auto s:ans){
	printf("%zu ",s.size());
	for(auto v:s){
	    printf("%d ",v);
	}
	puts("");
    }
}
int main(){
    freopen("cactus.in","r",stdin);
    freopen("cactus.out","w",stdout);
    string s;
    cin>>s;
    auto p=s.begin();
    shared_ptr<expr> exp=read_statement(s,p);
    exp->print(0);
    env global=env();
    graph grf=any_cast<graph>(exp->eval(global));
    rebuild(grf.l,grf.r);
    euler();
}
