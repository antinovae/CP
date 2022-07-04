#include<bits/stdc++.h>
using namespace std;
const int maxn=300005;
int n;
long long ans;
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
}e[maxn];
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
	    if(head==NULL||tail==NULL)head=NULL,tail=NULL;
	}
	void pop_back(){
	    if(this!=p){get()->pop_back();return;}
	    tail=tail->pre();
	    if(tail)tail->nxt()=NULL;
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
int merge(int x,int y){
    if(!x||!y)return x|y;
    x=find(x),y=find(y);
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
    int fl=0;
    for(auto u=a->front(),v=b->front();;u=u->nxt(),v=v->nxt()){
	if(u==a->back()){fl=0; break; }
	else if(v==b->back()){fl=1;break;}
    }
    if(!fl){
	vector<edge*>e;
	for(auto v=a->front();v;v=v->nxt()){
	    e.push_back(v);
	    if(v==a->back())break;
	}
	for(auto v:e)v->swp();
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
    if(pre)pre=pre->get();
    if(pre&&g[x].size()==1)return x;
    int sum,mer;
    if(!pre)sum=sz[x],mer=x;
    else sum=0,mer=new_node();
    vector<int>hole;
    for(auto &v:g[x]){
	v=v->get();
	if(v==pre)continue;
	if(!con(x,*v)){
	    v->reverse();
	}
	int cur=v->front()->u() + v->front()->v() - find(x);
	v->pop_front();
	hole.push_back(cur);
	ans+=1ll*sum*sz[cur];
	sum+=sz[cur];
    }
    auto G=g[x];g[x].resize(0);
    for(auto &v:G){
	v=v->get();
	if(v==pre){
	    g[mer].push_back(v);
	    continue;
	}
	if(v->R){
	    int nR=dfs(v->R,v);
	    if(nR!=v->R){
		g[mer].push_back(v);v->L=mer;
		e[++kl]=(edge){v->R,nR};
		ed[v->R].resize(0);
		ed[v->R].push_back(v->back());
		ed[v->R].push_back(&e[kl]);
		v->push_back(e[kl]);
		v->R=nR;
	    }
	    else if(v->front()){
		if(v->R!=x){
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
    if(x->pre())x->pre()->nxt()=x->nxt();
    if(x->nxt())x->nxt()->pre()=x->pre();
}
int is_cross(int x){
    for(auto v:g[x]){
	if(v->L==x||v->R==x)return 1;
    }
    return 0;
}
void beats(int x,chain* fa){
    if(fa){
	fa=fa->get();
	if(fa->R!=x)fa->reverse();
    }
    if(g[x].size()==1&&fa)return;
    if(g[x].size()==2&&fa){
	auto v=g[x].front()+(g[x].back()-fa->get());
	g[x].resize(0);
	if(v->L!=x){
	    v->reverse();
	}
	v=v->get();
	beats(v->R,v);
	samefy(fa,v);
	v->front()->pre()=fa->back();
	fa->back()->nxt()=v->front();
	ed[x].resize(0);
	ed[x].push_back(fa->back());
	ed[x].push_back(v->front());
	fa->R=v->R;
	fa->back()=v->back();
	v->get()->p=fa->get();
    }
    else{
	for(auto v:g[x]){
	    if(v==fa)continue;
	    beats(v->R,v->get());
	}
    }
}
void modify(int x){
    x=find(x);
    if(sz[x]==n)return;
    if(is_cross(x)){
	dfs(x,0);
	beats(x,0);
    }
    else{
	edge *L=ed[x][0],*R=ed[x][1];
	ed[x].resize(0);
	chain *c=L->col->get();
	if(R->pre()!=L&&L->pre()!=R)assert(0);
	if((R->pre()!=L))swap(L,R);
	int l=L->u()+L->v()-find(x),r=R->u()+R->v()-find(x);
	int ul=dfs(c->L,c);
	while(c->back()&&(L==c->front()||R==c->front())){
	    c->pop_front();
	}
	auto pl=L->pre();
	del(L);
	if(ul!=c->L){
	    e[++kl]={c->L,ul};
	    ed[c->L].resize(0);
	    ed[c->L].push_back(&e[kl]);
	    ed[c->L].push_back(c->front());
	    c->push_front(e[kl]);
	    c->L=ul;
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
	    if(nr)ed[x].push_back(nr);
	    else ed[x].push_back(&e[kl]);
	}
	else{
	    ed[x].push_back(nr);
	}
	ans+=1ll*sz[l]*sz[r]+1ll*sz[x]*sz[l]+1ll*sz[x]*sz[r];
	merge(x,l);merge(x,r);
	if(sz[x]==n)return;
	g[x].splice(g[x].end(),g[l]);
	g[x].splice(g[x].end(),g[r]);
	beats(c->L,0);
	if(ed[x][0])ed[x][0]->nxt()=ed[x][1];
	if(ed[x][1])ed[x][1]->pre()=ed[x][0];
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
signed main(){
    freopen("squirrel.in","r",stdin);
    freopen("squirrel.out","w",stdout);
    scanf("%d",&n);
    indec=n;
    for(int i=1;i<=n;i++)sz[i]=1,fa[i]=i;
    for(int i=1;i<n;i++){
	int x,y;
	scanf("%d%d",&x,&y);
	e[++kl]=(edge){x,y};
	_g[x].push_back(kl);
	_g[y].push_back(kl);
	ed[x].push_back(&e[kl]);
	ed[y].push_back(&e[kl]);
    }
    dfsp(1,0,0);
    for(int i=1;i<=idx;i++){
	g[t[i].L].push_back(&t[i]);
	g[t[i].R].push_back(&t[i]);
    }
    int Q;
    scanf("%d",&Q);
    while(Q--){
	int x;scanf("%d",&x);
	modify(x);
	printf("%lld\n",ans);
    }
}
