#include<bits/stdc++.h>
#include <unistd.h>
#define int long long

std::stringstream _cout;
/* #define cout _cout */

using namespace std;
const int maxn=100005;
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
    public:
	edge *_pre,*_nxt;
	int x,y;
	chain *col;
	edge(int u,int v){
	    x=u,y=v;
	    _pre=_nxt=NULL;
	}
	edge()=default;
	int u(){return find(x);}
	int v(){return find(y);}
	edge* &pre();
	edge* &nxt();
}e[maxn];
class chain{
    private:
    public:
	edge *head,*tail;
	int l,r;
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
	    if(head==NULL||tail==NULL)head=NULL,tail=NULL;
	}
	void pop_back(){
	    if(this!=p){get()->pop_back();return;}
	    tail=tail->pre();
	    if(head==NULL||tail==NULL)head=NULL,tail=NULL;
	}
	void push_front(edge &p){
	    if(this!=this->p){get()->push_front(p);return;}
	    p.col=this;
	    if(head==NULL||tail==NULL)head=tail=&p;
	    else{
		head->pre()=&p,p.nxt()=head,head=&p;
	    }
	}
	void push_back(edge &p){
	    if(this!=this->p){get()->push_back(p);return;}
	    p.col=this;
	    if(tail==NULL||head==NULL)head=tail=&p;
	    else{
		tail->nxt()=&p,p.pre()=tail,tail=&p;
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
int idx=0;
int dfs(int x,chain* pre){
    cout<<endl<<"DFS "<<x<<' '<<pre<<endl;
    if(pre)pre=pre->get();
    if(pre&&g[x].size()==1)return x;
    int sum=0,mer=new_node();
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
	cout<<"chain "<<v<<' '<<x<<" front "<<v->front()->u()<<" "<<v->front()->v()<<" L R "<<v->L<<' '<<v->R<<endl;
	cout<<v->tag<<" "<<v->front()->pre()<<" "<<v->front()->nxt()<<endl;
	/* cout<<v->tag<<" "<<v->front()->_pre<<" "<<v->front()->_nxt<<endl; */
	cout<<v->front()->col<<" "<<v<<endl;
	int cur=v->front()->u() + v->front()->v() - find(x);
	v->pop_front();
	cout<<v->front()<<endl;
	cout<<"chain "<<v<<' '<<x<<" front "<<v->front()->u()<<" "<<v->front()->v()<<" L R "<<v->L<<' '<<v->R<<endl;
	hole.push_back(cur);
	ans+=sum*sz[cur];
	sum+=sz[cur];
    }
    cout<<"mer: "<<mer<<" "<<ans<<" "<<sum<<endl;
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
		cout<<v->R<<" != "<<x<<endl;
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

void del(edge &x){
    if(x.pre())x.pre()->nxt()=x.nxt();
    if(x.nxt())x.nxt()->pre()=x.pre();
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
    /* cout<<"beats! "<<x<<endl; */
    if(g[x].size()==1&&fa)return;
    if(g[x].size()==2&&fa){
	auto v=g[x].front()+(g[x].back()-fa->get());
	g[x].resize(0);
	if(v->L!=x)v->reverse();
	/* cout<<"merge "<<fa->L<<' '<<fa->R<<' '<<v->L<<' '<<v->R<<endl; */
	v=v->get();
	beats(v->R,v);
	v->front()->pre()=fa->back();
	fa->back()->nxt()=v->front();
	ed[x].resize(0);
	ed[x].push_back(v->front());
	ed[x].push_back(fa->back());
	update(v->front()->u() + v->front()->v() - v->L, x,v->front());
	update(fa->back()->u() + fa->back()->v() - fa->R, x,fa->back());

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
void modify(int x){
    x=find(x);
    cout<<"MODIFY: "<<x<<endl;
    cout<<"is cross? :"<<is_cross(x)<<endl;
    if(sz[x]==n)return;
    if(is_cross(x)){
	pr(x,0);
	dfs(x,0);
	pr(x,0);
	beats(x,0);
	pr(x,0);
    }
    else{
	edge *L=ed[x][0],*R=ed[x][1];
	chain *c=L->col->get();
	if(R->pre()!=L&&L->pre()!=R)assert(0);
	if((R->pre()!=L))swap(L,R);
	ed[x].resize(0);
	t[++idx].L=c->L;t[idx].R=x;t[idx].front()=c->front();t[idx].back()=L;
	t[idx].reverse();
	for(auto &v:g[c->L]){
	    if(v==c)v=&t[idx];
	}
	g[x].push_back(&t[idx]);
	t[++idx].L=x;t[idx].R=c->R;t[idx].front()=R;t[idx].back()=c->back();
	for(auto &v:g[c->R]){
	    if(v==c)v=&t[idx];
	}
	g[x].push_back(&t[idx]);
	pr(x,0);
	dfs(x,0);
	pr(x,0);
	beats(x,0);
	pr(x,0);
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
	if(v==fa)continue;
	pr(v->get()->R,v->get());
    }
}


signed main(){
    /* freopen("squirrel.in","r",stdin); */
    /* freopen("squirrel.out","w",stdout); */
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
    pr(1,0);
	for(int i=1;i<=kl;i++){
	    cout<<&e[i]<<"  "<<e[i].u()<<' '<<e[i].v()<<"   "<<e[i].pre()<<' '<<e[i].nxt()<<endl;
	}
    scanf("%lld",&Q);
    while(Q--){
	int x;scanf("%lld",&x);
	modify(x);
	printf("%lld\n",ans);
	/* for(int i=1;i<=indec;i++){ */
	/*     if(i!=find(i))continue; */
	/*     cout<<i<<" "<<sz[i]<<endl; */
	/*     for(auto v:ed[i]){ */
	/* 	if(v)cout<<i<<"  "<<v->u()<<" "<<v->v()<<" prenxt "<<v->pre()<<" "<<v->nxt()<<endl; */
	/*     } */
	/* } */
    }
}

