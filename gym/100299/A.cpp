#include<bits/stdc++.h>
using namespace std;
const int maxn=201;
mt19937 rnd(114514);
int n,m,a[maxn][maxn],b[maxn][maxn],bs[maxn][maxn],bb[maxn][maxn];
struct group{
    int c[2][2],to[2][2];
    int v[4],_x[2],_y[2];
    vector<pair<int,int>>op;
    void init(int x,int y){
	op.resize(0);
	_x[0]=x;_y[0]=y;
	_x[1]=n-x+1;_y[1]=m-y+1;
	c[0][0]=a[x][y]; to[0][0]=b[x][y];
	c[0][1]=a[x][m-y+1]; to[0][1]=b[x][m-y+1];
	c[1][0]=a[n-x+1][y]; to[1][0]=b[n-x+1][y];
	c[1][1]=a[n-x+1][m-y+1]; to[1][1]=b[n-x+1][m-y+1];
	v[0]=c[0][0],v[1]=c[0][1],v[2]=c[1][0],v[3]=c[1][1];
	/* cout<<c[0][0]<<" "<<c[0][1]<<" "<<c[1][0]<<" "<<c[1][1]<<endl; */
	/* cout<<to[0][0]<<" "<<to[0][1]<<" "<<to[1][0]<<" "<<to[1][1]<<endl; */
    }
    int check(){
	sort(v,v+4);
	if(v[0]!=to[0][0]||v[1]!=to[0][1]||v[2]!=to[1][0]||v[3]!=to[1][1])return 0;
	return 1;
    }
    int type(){
	int tp=0;
	v[0]=c[0][0],v[1]=c[0][1],v[2]=c[1][0],v[3]=c[1][1];
	/* for(int i=0;i<4;i++)cout<<v[i]<<" "; */
	for(int i=0;i<4;i++)for(int j=i+1;j<4;j++)if(v[i]>v[j])tp^=1;
	/* cout<<tp<<endl; */
	return tp;
    }
    void rotate(int x,int y){
	swap(c[x][0],c[x][1]); op.push_back({_x[x],0});
	swap(c[0][y],c[1][y]); op.push_back({_y[y],1});
	swap(c[x][0],c[x][1]); op.push_back({_x[x],0});
	swap(c[0][y],c[1][y]); op.push_back({_y[y],1});
	/* cout<<c[0][0]<<" "<<c[0][1]<<" "<<c[1][0]<<" "<<c[1][1]<<endl; */
	/* cout<<to[0][0]<<" "<<to[0][1]<<" "<<to[1][0]<<" "<<to[1][1]<<endl; */
    }
    void construct(){
	while(c[0][0]!=to[0][0]&&c[0][1]!=to[0][1]&&c[1][0]!=to[1][0]&&c[1][1]!=to[1][1]){
	    rotate(rnd()%2,rnd()%2);
	    /* system("sleep 0.5"); */
	}
	/* puts("ok"); */
	for(int i:{0,1})for(int j:{0,1}){
	    if(c[i][j]==to[i][j]){
		while(c[0][0]!=to[0][0]||c[0][1]!=to[0][1]||c[1][0]!=to[1][0]||c[1][1]!=to[1][1])
	    /* system("sleep 0.5"), */
		    rotate(i^1,j^1);
		break;
	    }
	}
    }
}t[maxn][maxn];
vector<pair<int,int>>oper;
void flip_x(int pos){
    oper.push_back({pos,0});
    for(int i=1;i<=m/2;i++)bb[pos][i]^=1;
}
void flip_y(int pos){
    oper.push_back({pos,1});
    for(int i=1;i<=n/2;i++)bb[i][pos]^=1;
}
void operate_x(int pos){
    for(int i=1;i<=m/2;i++)swap(a[pos][i],a[pos][m-i+1]);
}
void operate_y(int pos){
    for(int i=1;i<=n/2;i++)swap(a[i][pos],a[n-i+1][pos]);
}
int check(int p){
    oper.resize(0);
    for(int i=1;i<=n/2;i++)for(int j=1;j<=m/2;j++)bb[i][j]=bs[i][j];
    if(p)flip_x(1);
    for(int i=1;i<=m/2;i++){
	if(bb[1][i])flip_y(i);
    }
    for(int i=1;i<=n/2;i++){
	if(bb[i][1])flip_x(i);
    }
    for(int i=1;i<=n/2;i++)for(int j=1;j<=m/2;j++){
	if(bb[i][j])return 0;
    }
    return 1;
}
void pr(){
    for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++)cout<<a[i][j]<<" ";
	puts("");
    }
    puts("");
}
int _main(){
    oper.resize(0);
    scanf("%d%d",&m,&n);
    int indec=0;
    for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
	    scanf("%d",&a[i][j]);
	    b[i][j]=++indec;
	}
    }
    for(int i=1;i<=n/2;i++){
	for(int j=1;j<=m/2;j++){
	    t[i][j].init(i,j);
	    if(!t[i][j].check())return 0;
	    bs[i][j]=t[i][j].type();
	    /* cout<<bs[i][j]<<" "; */
	}
	/* cout<<endl; */
    }
    if(!check(0)&&!check(1))return 0;
    for(auto [v,tp]:oper){
	if(!tp)operate_x(v);
	else operate_y(v);
    }
    /* puts("here "); */
    /* pr(); */
    for(int i=1;i<=n/2;i++){
	for(int j=1;j<=m/2;j++){
	    t[i][j].init(i,j);
	    t[i][j].construct();
	    for(auto [v,tp]:t[i][j].op){
		oper.push_back({v,tp});
		if(!tp)operate_x(v);
		else operate_y(v);
	    }
	}
    }
    if(n%2==1){
	int ps=n/2+1;
	if(![&]{
	for(int i=1;i<=m;i++)if(a[ps][i]!=b[ps][i])return 0;
	    return 1;
	}()){
	    oper.push_back({ps,0});operate_x(ps);
	}
	/* pr(); */
	if(![&]{
	for(int i=1;i<=m;i++)if(a[ps][i]!=b[ps][i])return 0;
	    return 1;
	}())return 0;
    }
    if(m%2==1){
	int ps=m/2+1;
	if(![&]{
	for(int i=1;i<=n;i++)if(a[i][ps]!=b[i][ps])return 0;
	    return 1;
	}()){
	    oper.push_back({ps,1});operate_y(ps);
	}
	/* pr(); */
	if(![&]{
	for(int i=1;i<=n;i++)if(a[i][ps]!=b[i][ps])return 0;
	    return 1;
	}())return 0;
    }
    printf("POSSIBLE ");
    printf("%zu ",oper.size());
    for(auto [v,tp]:oper){
	if(!tp)putchar('R'),printf("%d ",v);
	else putchar('C'),printf("%d ",v);
    }
    puts("");
    /* pr(); */
    return 1;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
	if(!_main())puts("IMPOSSIBLE");
    }
}
