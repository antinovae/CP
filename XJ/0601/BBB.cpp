#include<bits/stdc++.h>
#include <unistd.h>
#define int long long

std::stringstream _cout;
#define cout _cout

using namespace std;
const int maxn=300005;
int n;
int ans=0;
int fa[maxn],sz[maxn];
int find(int x){
    return (x==fa[x])?x:fa[x]=find(fa[x]);
}
int kl;
class edge;
class chain;
class edge{
    private:
	edge *_pre,*_nxt;
	int x,y;
    public:
	chain *col;
	edge(int u,int v){
	    x=u,y=v;
	    _pre=_nxt=NULL;
	}
	edge()=default;
	int u(){return find(x);}
	int v(){return find(y);}
	void swp(){
	    swap(_pre,_nxt);
	}
	edge* &pre();
	edge* &nxt();
	void pr();

}e[maxn];
void edge::pr(){
    cout<<"uv: "<<u()<<' '<<v()<<" prenxt "<<pre()-e<<" "<<nxt()-e<<endl;
}
class chain{
    private:
	edge *head,*tail;
	int l,r;
    public:
	int tag;
	chain *p;
	struct L_proxy{
	    chain *c;
	    L_proxy &operator=(int val){c->get()->l=find(val);return*this;}
	    L_proxy &operator=(const L_proxy &val){c->get()->l=(int)val;return*this;}
	    operator int()const{return find(c->get()->l);}
	}L{this};
	struct R_proxy{
	    chain *c;
	    R_proxy &operator=(int val){c->get()->r=find(val);return*this;}
	    R_proxy &operator=(const R_proxy &val){c->get()->r=(int)val;return*this;}
	    operator int()const{return find(c->get()->r);}
	}R{this};
	chain &operator=(chain) = delete;
	chain &operator=(chain&&) = delete;
	chain(edge *_head,edge *_tail,int l,int r){
	    p=this;
	    head=_head;
	    tail=_tail;
	    L=l;
	    R=r;
	}
	chain(){p=this;}
	chain *get(){
	    return p==this?p:p=p->get();
	}
	edge *&front(){
	    return get()->head;
	}
	edge *&back(){
	    return get()->tail; 
	}
	void pop_front(){
	    if(this!=p){get()->pop_front();return;}
	    head=head->nxt();
	    if(head)head->pre()=NULL;
	    /* while(head&&head->u()==head->v())head=head->nxt(); */
	    if(head==NULL||tail==NULL)head=NULL,tail=NULL;
	}
	void pop_back(){
	    if(this!=p){get()->pop_back();return;}
	    tail=tail->pre();
	    if(tail)tail->nxt()=NULL;
	    /* while(tail&&tail->u()==tail->v())tail=tail->pre(); */
	    if(head==NULL||tail==NULL)head=NULL,tail=NULL;
	}
	void push_front(edge &p){
	    if(this!=this->p){get()->push_front(p);return;}
	    p.col=this;
	    if(head==NULL||tail==NULL)head=tail=&p;
	    else{
		head->pre()=&p,p.nxt()=head,head=&p;
		p.pre()=NULL;
	    }
	}
	void push_back(edge &p){
	    if(this!=this->p){get()->push_back(p);return;}
	    p.col=this;
	    if(tail==NULL||head==NULL)head=tail=&p;
	    else{
		tail->nxt()=&p,p.pre()=tail,tail=&p;
		p.nxt()=NULL;
	    }
	}
	void reverse(){
	    if(this!=this->p){get()->reverse();return;}
	    swap(head,tail);
	    tag^=1;
	    int tmp=L;
	    L=R;
	    R=tmp;
	}
}t[maxn];
edge* &edge::pre(){
    if(!col||!col->get()->tag)return _pre;
    else return _nxt;
}
edge* &edge::nxt(){
    if(!col||!col->get()->tag)return _nxt;
    else return _pre;
}
list<chain*>g[maxn];
vector<edge *>ed[maxn];
void pr(int,chain*);
int merge(int x,int y){
    if(!x||!y)return x|y;
    x=find(x),y=find(y);
    /* if(sz[x]<sz[y])swap(x,y); */
    sz[x]+=sz[y];fa[y]=x;
    return x;
}
int con(int x,chain &t){
    return t.L==x;
}
int indec=0;
int new_node(){
    ++indec;
    fa[indec]=indec;
    return indec;
}
void samefy(chain* &a,chain* &b){
    if(a->tag==b->tag)return;
    cout<<"SAMEFY! "<<a->L<<" "<<a->R<<" "<<b->L<<" "<<b->R<<endl;
    int fl=0;
    for(auto u=a->front(),v=b->front();;u=u->nxt(),v=v->nxt()){
	if(u==a->back()){fl=0; break; }
	else if(v==b->back()){fl=1;break;}
    }
    cout<<"fl: "<<fl<<endl;
    if(!fl){
	a->front()->pr();
	a->back()->pr();
	vector<edge*>e;
	for(auto v=a->front();v;v=v->nxt()){
	    e.push_back(v);
	    /* cout<<v->u()<<" "<<v->v()<<endl; */
	    if(v==a->back())break;
	}
	for(auto v:e)v->swp();
	a->front()->pr();
	a->back()->pr();
	a->tag^=1;
    }
    else{
	vector<edge*>e;
	for(auto v=b->front();v;v=v->nxt()){
	    e.push_back(v);
	    if(v==b->back())break;
	}
	for(auto v:e)v->swp();
	b->tag^=1;
    }
}
int idx=0;
int dfs(int x,chain* pre){
    cout<<endl<<"DFS "<<x<<' '<<pre<<endl;
    if(pre)pre=pre->get();
    if(pre&&g[x].size()==1)return x;
    int sum,mer;
    if(!pre)sum=sz[x],mer=x;
    else sum=0,mer=new_node();
    cout<<"mer: "<<mer<<" "<<ans<<" "<<sum<<endl;
    vector<int>hole;
    for(auto &v:g[x]){
	v=v->get();
	if(v==pre)continue;
	if(!con(x,*v)){
	    v->reverse();
	    cout<<"reversed"<<endl;
	}
	if(v->front())cout<<"chain "<<v<<' '<<x<<" front "<<v->front()-e<<" "<<v->front()->u()<<" "<<v->front()->v()<<" L R "<<v->L<<' '<<v->R<<endl;
	/* cout<<v->tag<<" "<<v->front()->pre()<<" "<<v->front()->nxt()<<endl; */
	/* cout<<v->tag<<" "<<v->front()->_pre<<" "<<v->front()->_nxt<<endl; */
	/* cout<<v->front()->col<<" "<<v<<endl; */
	int cur=v->front()->u() + v->front()->v() - find(x);
	v->pop_front();
	/* cout<<v->front()<<endl; */
	if(v->front())cout<<"chain "<<v<<' '<<x<<" front "<<v->front()-e<<" "<<v->front()->u()<<" "<<v->front()->v()<<" L R "<<v->L<<' '<<v->R<<endl;
	/* exit(0); */
	hole.push_back(cur);
	ans+=sum*sz[cur];
	sum+=sz[cur];
    }
    /* cout<<"mer: "<<mer<<" "<<ans<<" "<<sum<<endl; */
    auto G=g[x];g[x].resize(0);
    for(auto &v:G){
	v=v->get();
	if(v==pre){
	    g[mer].push_back(v);
	    continue;
	}
	if(v->R){
	    int nR=dfs(v->R,v);
	    cout<<"vR: "<<v->R<<endl;
	    cout<<"nR: "<<nR<<endl;
	    cout<<v->front()<<" "<<v->back()<<endl;
	    if(nR!=v->R){
		g[mer].push_back(v);v->L=mer;
		cout<<"pushback "<<mer<<' '<<v<<endl;
		e[++kl]=(edge){v->R,nR};
		ed[v->R].resize(0);
		ed[v->R].push_back(v->back());
		ed[v->R].push_back(&e[kl]);
		v->push_back(e[kl]);
		/* cout<<v->back()<<endl; */
		v->R=nR;
	    }
	    else if(v->front()){
		/* cout<<v->R<<" != "<<x<<endl; */
		if(v->R!=x){
		    cout<<"pushback "<<mer<<' '<<v<<endl;
		    g[mer].push_back(v);v->L=mer;
		}
	    }
	}
    }
    for(auto cur:hole)mer=merge(mer,cur); 
    return mer;
}
int same(edge a,edge b){
    return a.u()==b.u()&&a.v()==b.v();
}

void del(edge* &x){
    cout<<"	DELETE!! "<<x<<endl;
    if(x->pre())x->pre()->nxt()=x->nxt();
    if(x->nxt())x->nxt()->pre()=x->pre();
}
int is_cross(int x){
    for(auto v:g[x]){
	if(v->L==x||v->R==x)return 1;
    }
    return 0;
}
void update(int x,int ex,edge *p){
    /* cout<<"update: "<<x<<' '<<ex<<endl; */
    /* cout<<p->u()<<' '<<p->v()<<endl; */
    for(auto &v:ed[x]){
	/* cout<<v->u()<<' '<<v->v()<<" "<<" "<<find(x)<<" "<<find(ex)<<endl; */
	if(v->u()+v->v()-find(x)==find(ex)){
	    /* cout<<"updated! "<<endl; */
	    v=p;
	}
    }
}
void beats(int x,chain* fa){
    if(fa){
	fa=fa->get();
	if(fa->R!=x)fa->reverse();
    }
    cout<<"beats! "<<x<<endl;
    if(g[x].size()==1&&fa)return;
    if(g[x].size()==2&&fa){
	auto v=g[x].front()+(g[x].back()-fa->get());
	g[x].resize(0);
	if(v->L!=x){
	    v->reverse();
	    cout<<"reversed"<<endl;
	}
	cout<<"merge "<<fa->L<<' '<<fa->R<<' '<<v->L<<' '<<v->R<<endl;
	v=v->get();
	beats(v->R,v);
	cout<<fa->tag<<" "<<v->tag<<endl;
	for(auto v=fa->front();;v=v->nxt()){
	    cout<<v->u()<<" "<<v->v()<<endl;if(v==fa->back())break;
	}
	for(auto _v=v->front();;_v=_v->nxt()){
	    cout<<_v->u()<<" "<<_v->v()<<endl;if(_v==v->back())break;
	}

	samefy(fa,v);


	v->front()->pre()=fa->back();
	fa->back()->nxt()=v->front();
	ed[x].resize(0);
	ed[x].push_back(fa->back());
	ed[x].push_back(v->front());
	/* update(v->front()->u() + v->front()->v() - v->L, x,v->front()); */
	/* update(fa->back()->u() + fa->back()->v() - fa->R, x,fa->back()); */
	fa->R=v->R;
	fa->back()=v->back();
	v->get()->p=fa->get();
	/* cout<<fa->L<<' '<<fa->R<<endl; */
    }
    else{
	for(auto v:g[x]){
	    if(v==fa)continue;
	    beats(v->R,v->get());
	}
    }
}
void pr_chain(){
    for(int i=1;i<=indec;i++){
	if(i!=find(i))continue;
	cout<<"id: "<<i<<" sz: "<<sz[i]<<endl;
	for(auto v:ed[i]){
	    if(v)cout<<"-> "<<v-e<<"  uv:"<<v->u()<<" "<<v->v()<<" prenxt "<<v->pre()-e<<" "<<v->nxt()-e<<endl;
	}
    }
    for(int i=1;i<=kl;i++){
	cout<<&e[i]-e<<"  "<<e[i].u()<<' '<<e[i].v()<<"   "<<e[i].pre()-e<<' '<<e[i].nxt()-e<<endl;
    }
    cout<<endl;
    cout<<endl;
}
void modify(int x){
    x=find(x);
    cout<<"MODIFY: "<<x<<endl;
    cout<<"is cross? :"<<is_cross(x)<<endl;
    if(sz[x]==n)return;
    if(is_cross(x)){
	dfs(x,0);
	pr(x,0);
	pr_chain();
	beats(x,0);
	pr(x,0);
	pr_chain();
    }
    else{
	edge *L=ed[x][0],*R=ed[x][1];
	ed[x].resize(0);
	chain *c=L->col->get();
	cout<<L<<" "<<R<<" pp "<<L->pre()<<" "<<R->pre()<<endl;
	if(R->pre()!=L&&L->pre()!=R)assert(0);
	if((R->pre()!=L))swap(L,R);
	int l=L->u()+L->v()-find(x),r=R->u()+R->v()-find(x);
	int ul=dfs(c->L,c);
	while(c->back()&&(L==c->front()||R==c->front())){
	    /* auto tmp=c->front(); */
	    c->pop_front();
	    /* del(tmp); */
	}
	auto pl=L->pre();
	del(L);
	if(ul!=c->L){
	    e[++kl]={c->L,ul};
	    ed[c->L].resize(0);
	    ed[c->L].push_back(&e[kl]);
	    ed[c->L].push_back(c->front());
	    c->push_front(e[kl]);
	    /* cout<<&e[kl]<<" "<<e[kl].pre()<<" uuu  "<<e[kl].nxt()<<endl; */
	    c->L=ul;
	    cout<<"ready "<<pl<<" "<<&e[kl]<<endl;
	    if(pl)ed[x].push_back(pl);
	    else {
		ed[x].push_back(&e[kl]);
	    }
	}
	else{
	    ed[x].push_back(pl);
	}
	int ur=dfs(c->R,c);
	while(c->back()&&(R==c->back()||L==c->back())){
	    c->pop_back();
	}
	auto nr=R->nxt();
	del(R);
	if(ur!=c->R){
	    e[++kl]={c->R,ur};
	    ed[c->R].resize(0);
	    ed[c->R].push_back(&e[kl]);
	    ed[c->R].push_back(c->back());
	    c->push_back(e[kl]);
	    c->R=ur;
	    cout<<"ready "<<nr<<" "<<&e[kl]<<endl;
	    if(nr)ed[x].push_back(nr);
	    else ed[x].push_back(&e[kl]);
	}
	else{
	    ed[x].push_back(nr);
	}
	/* pr(c->L,c); */
	/* pr(c->R,c); */
	/* cout<<l<<" "<<r<<" "<<ul<<' '<<ur<<endl; */
	/* cout<<c->L<<" "<<c->R<<endl; */
	/* cout<<c->front()->u()<<" "<<c->front()->v()<<endl; */
	/* cout<<c->back()->u()<<" "<<c->back()->v()<<endl; */
	/* for(auto v:g[c->L]){ cout<<v<<" "; }//puts(""); */
	/* for(auto v:g[c->R]){ cout<<v<<" "; }//puts(""); */
	ans+=sz[l]*sz[r]+sz[x]*sz[l]+sz[x]*sz[r];
	merge(x,l);merge(x,r);
	if(sz[x]==n)return;
	/* pr(c->L,0); */
	g[x].splice(g[x].end(),g[l]);
	g[x].splice(g[x].end(),g[r]);
	pr(c->L,0);
	beats(c->L,0);
	pr(c->L,0);
	cout<<ed[x][0]<<"  awa "<<ed[x][1]<<endl;
	if(ed[x][0])ed[x][0]->nxt()=ed[x][1];
	if(ed[x][1])ed[x][1]->pre()=ed[x][0];




/* 	t[++idx].L=c->L;t[idx].R=x;t[idx].front()=c->front();t[idx].back()=L; */
/* 	t[idx].reverse(); */
/* 	for(auto &v:g[c->L]){ */
/* 	    if(v==c)v=&t[idx]; */
/* 	} */
/* 	g[x].push_back(&t[idx]); */
/* 	t[++idx].L=x;t[idx].R=c->R;t[idx].front()=R;t[idx].back()=c->back(); */
/* 	for(auto &v:g[c->R]){ */
/* 	    if(v==c)v=&t[idx]; */
/* 	} */
/* 	g[x].push_back(&t[idx]); */
/* 	dfs(x,0); */
/* 	pr(x,0); */
/* 	beats(x,0); */
/* 	pr(x,0); */
    }
}
vector<int>_g[maxn];
void dfsp(int x,int fa_edge,int id){
    if(_g[x].size()>=3||fa_edge==0){
	for(auto p:_g[x]){
	    if(p==fa_edge)continue;
	    int v=e[p].u()+e[p].v()-x;
	    id=++idx;
	    e[p].col=&t[id];
	    t[id].L=x,t[id].R=v; 
	    t[id].front()=t[id].back()=&e[p];
	    dfsp(v,p,id);
	}
    }
    else if(_g[x].size()==2){
	for(auto p:_g[x]){
	    if(p==fa_edge)continue;
	    e[p].pre()=&e[fa_edge],e[fa_edge].nxt()=&e[p];
	    int v=e[p].u()+e[p].v()-x;
	    e[p].col=&t[id];
	    t[id].R=v;
	    t[id].back()=&e[p];
	    dfsp(v,p,id);
	}
    }
}
int vis[maxn];
void pr(int x,chain *fa){
    x=find(x);
    /* usleep(500000); */
    cout<<"id: "<<x<<" size: "<<sz[x]<<endl;
    for(auto &v:g[x]){
	v=v->get();
	cout<<v<<endl;
	/* cout<<"range "<<t[v].front()->x<<" "<<t[v].front()->y<<"  "<<t[v].back()->x<<" "<<t[v].back()->y<<endl; */
	if(v->front())cout<<"front "<<v->front()->u()<<" "<<v->front()->v()<<endl;
	if(v->back())cout<<"back "<<v->back()->u()<<" "<<v->back()->v()<<endl;
	cout<<"node "<<v->L<<" "<<v->R<<endl;
    }
    for(auto &v:g[x]){
	v=v->get();
	if(v==fa||v->R==x)continue;
	pr(v->get()->R,v->get());
    }
}


signed main(){
    freopen("squirrel.in","r",stdin);
    freopen("squirrel.out","w",stdout);
    /* int x; */
    /* printf("&n = %p, &x = %p\n", &n, &x); */
    scanf("%lld",&n);
    indec=n;
    for(int i=1;i<=n;i++)sz[i]=1,fa[i]=i;
    for(int i=1;i<n;i++){
	int x,y;
	scanf("%lld%lld",&x,&y);
	e[++kl]=(edge){x,y};
	_g[x].push_back(kl);
	_g[y].push_back(kl);
	ed[x].push_back(&e[kl]);
	ed[y].push_back(&e[kl]);
    }
    dfsp(1,0,0);
    for(int i=1;i<=idx;i++){
	/* cout<<t[i].L<<' '<<t[i].R<<endl; */
	g[t[i].L].push_back(&t[i]);
	g[t[i].R].push_back(&t[i]);
    }
    /* for(int i=1;i<=indec;i++){ */
	/* if(i!=find(i))continue; */
	/* cout<<"cur: "<<i<<" "<<sz[i]<<endl; */
	/* for(auto v:ed[i]){ */
	    /* cout<<v->u()<<" "<<v->v()<<endl; */
	/* } */

    
    /* cout<<t[1].head->u()<<" "<<t[1].head->v()<<endl; */
	/* if(t[1].head->pre()!=NULL)cout<<"pre "; */
	/* if(t[1].head->nxt()!=NULL)cout<<"nxt "; */
    int Q;
	for(int i=1;i<=indec;i++){
	    if(i!=find(i))continue;
	    cout<<i<<" "<<sz[i]<<endl;
	    for(auto v:ed[i]){
		if(v)cout<<v<<"  "<<v->u()<<" "<<v->v()<<" prenxt "<<v->pre()<<" "<<v->nxt()<<endl;
	    }
	}
	for(int i=1;i<=kl;i++){
	    cout<<&e[i]<<"  "<<e[i].u()<<' '<<e[i].v()<<"   "<<e[i].pre()<<' '<<e[i].nxt()<<endl;
	}
    scanf("%lld",&Q);
    while(Q--){
	int x;scanf("%lld",&x);
	modify(x);
	cout<<"ans: ";
	printf("%lld\n",ans);

    }
}

