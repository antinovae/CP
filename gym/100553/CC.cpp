#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
vector<int>e[maxn];
int indec=0;
struct graph{int l,r;};
class env{
    private:
	unordered_map<string,int>binds;
    public:
	int cal(string name){
	    if(binds.find(name)==binds.end())return binds.find(name)->second;
	    else assert(0);
	}
	void add_bind(string name,int val=0){
	    if(binds.find(name)==binds.end())assert(0);
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
	string type;
	virtual graph cal_func(env &cur_env);
	virtual vector<any> cal_range(env &cur_env);
	virtual int cal_var(env &cur_env);
	virtual int cal_number(env &cur_env);
};
graph eval(expr cur,env cur_env);
graph C(const vector<any> &s);
graph loop(const vector<any> &s);
graph T(const vector<any> &s);
class func:public expr{
    private:
	string name;
	vector<expr>paras;
    public:
	template <class A, class B>
	func(A &&name, B &&paras) : name(std::forward<A>(name)), paras(std::forward<B>(paras)) {}
	graph cal_func(env &cur_env){
	    vector<any>_paras;
	    for(auto v:paras){
		_paras.push_back(eval(v,cur_env));
	    }
	    if(name=="c"){
		return C(_paras);
	    }
	    else if(name=="loop"){
		return loop(_paras);
	    }
	    else if(name=="T"){
		return T(_paras);
	    }
	    else assert(0);
	};
};
class range:public expr{
    public:
	string name;
	int l,r;
	expr body;
	vector<any> cal_range(env &cur_env){
	    vector<any>res;
	    cur_env.add_bind(name);
	    for(int i=l;i<=r;i++){
		cur_env.modify_bind(name,i);
		res.push_back(eval(body,cur_env));
	    }
	    cur_env.remove_bind(name);
	    return res;
	}
};
class variable:public expr{
    public:
	string s;
	int cal_var(env &cur_env){
	    return cur_env.cal(s);
	}
};
class number:public expr{
    public:
	int v;
	int cal_number(env &cur_env){return v;}
};
graph C(int x){
    for(int i=1;i<=x+1;i++){
	e[indec+i].push_back(indec+i+1);
    }
    graph res={indec+1,indec+x+1};
    indec+=x+1;
    return res;
}
graph C(){return C(1);}
graph C(const vector<graph> &s){
    for(int i=0;i<s.size()-1;i++){
	e[s[i].r].push_back(s[i+1].l);
    }
    return {s[0].l,s.back().r};
}
graph C(const vector<any> &s){
    if(s.empty())return C();
    else if(s.size()==1&&s[0].type()==typeid(int))return C(any_cast<int>(s[0]));
    else{
	vector<graph>t;
	for(auto v:s)t.push_back(any_cast<graph>(v));
	return C(t);
    }
}
graph loop(const vector<graph> &s){
    auto [l,r]=C(s);
    e[r].push_back(l);
    return *s.begin(); 
}
graph loop(int x){
    auto [l,r]=C(x);
    return {l,l+1};
}
graph loop(const vector<any> &s){
    if(s.size()==1&&s[0].type()==typeid(int))return loop(any_cast<int>(s[0]));
    else{
	vector<graph>t;
	for(auto v:s)t.push_back(any_cast<graph>(v));
	return loop(t);
    }
}
graph T(int x){
    int l=++indec;
    for(int i=1;i<=x;i++){
	e[l].push_back(++indec);
    }
    return {l,l+1};
}
graph T(const vector<graph> &s){
    int l=++indec;
    for(auto v:s){
	if(e[l].size()>e[v.l].size())
	    for(auto u:e[v.l])e[l].push_back(u);
	else for(auto u:e[l])e[v.l].push_back(u);
    }
    return {l,s.begin()->r};
}
graph T(const vector<any> &s){
    if(s.size()==1&&s[0].type()==typeid(int))return T(any_cast<int>(s[0]));
    else{
	vector<graph>t;
	for(auto v:s)t.push_back(any_cast<graph>(v));
	return T(t);
    }
}
any eval(expr &cur_expr,env &cur_env){
    if(cur_expr.type=="function"){
	return cur_expr.cal_func(cur_env);
    }
    else if(cur_expr.type=="range"){
	return cur_expr.cal_range(cur_env);
    }
    else if(cur_expr.type=="variable"){
	return cur_expr.cal_var(cur_env);
    }
    else if(cur_expr.type=="number"){
	return cur_expr.cal_number(cur_env); 
    }
    assert(0);
}
string range(string &s,int l,int r){
    return s.substr(l,r-l);

}
expr split(string &s);
vector<expr> split_paras(string &s){
    vector<expr>paras;
    int pos=s.find('(')+1;
    while(pos!=string::npos&&pos<s.size()){
	auto nxt=min(s.find(','),s.find(')'));
	if(nxt==string::npos)break;
	string body=range(s,pos,nxt);
	paras.push_back(split(body));
	pos=nxt+1;
    }
    return paras;
}
expr split(string &s){
    if(s.find("loop")==0){
	string name="loop";
	vector<expr> paras=split_paras(s);
	func cur=(func){name,paras};
    }
    if(s.find("c")==0){
	string name="c";
	vector<expr> paras=split_paras(s);
	func cur=(func){name,paras};
    }
    if(s.find("t")==0){
	string name="t";
	vector<expr> paras=split_paras(s);
	func cur=(func){name,paras};
    }
    if(s.find("range")==0){
	string name="t";
	vector<expr> paras=split_paras(s);
	func cur=(func){name,paras};
    }

}
int main(){
    string s;
    cin>>s;
    expr expr=split(s);
}
