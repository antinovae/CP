#include<bits/stdc++.h>
using namespace std;
const int maxn=101;
int n,m,K,H,W,vis[maxn];
char s[maxn][maxn],res[maxn][maxn];
void print(){
    for(int i=1;i<=n*H;i++){
	for(int j=1;j<=n*W;j++){
	    putchar(res[i][j]);
	}
	puts("");
    }
}
vector<tuple<int,int,char>>a[maxn];
int tp[maxn][4];
int out(int x,int y){
    if(x<1||y<1||x>n*H||y>n*W)return 1;
    return 0;
}
int check(int x,int y){
    /* cout<<x<<" "<<y<<endl; */
    /* print(); */
    if(x<0)return 1;
    for(int i=x;i<=x+H-1;i++){
	for(int j=y;j<=y+W-1;j++){
	    /* cout<<i<<" "<<j<<" "<<res[i][j]<<endl; */
	    if(res[i][j]=='.')return 0;
	}
	/* cout<<endl; */
    }
    return 1;
}
void dfs(int x,int y){
    /* cout<<x<<" "<<y<<endl; */
	/* print(); */
    if(x>n*H){
	print();
	exit(0);
	return;
    }
    for(int i=1;i<=K;i++){
	if((x==1)!=tp[i][0])continue;
	if((y+W-1==n*W)!=tp[i][1])continue;
	if((x+H-1==n*H)!=tp[i][2])continue;
	if((y==1)!=tp[i][3])continue;
	if(vis[i])continue;
	/* cout<<"choose "<<i<<endl; */
	    int fl=1;
	    for(auto [_x,_y,c]:a[i]){
		if(res[x+_x][y+_y]!='.'||out(x+_x,y+_y)){fl=0;break;}
	    }
	    if(!fl)continue;
	    for(auto [_x,_y,c]:a[i])res[x+_x][y+_y]=c;
	    vis[i]=1;
	    if(check(x-H,y)){
		if(y+W>n*W)dfs(x+H,1);
		else dfs(x,y+W);
	    }
	    for(auto [_x,_y,c]:a[i])res[x+_x][y+_y]='.';
	    vis[i]=0;
    }
}
int main(){
    freopen("ascii.in","r",stdin);
    freopen("ascii.out","w",stdout);
    scanf("%d%d%d",&K,&W,&H);
    n=sqrt(K);
    for(int k=1;k<=K;k++){
	for(int i=1;i<=3*H-2;i++){
	    scanf("%s",s[i]+1);
	    for(int j=1;j<=3*W-2;j++){
		if(s[i][j]!='.'){
		    /* cout<<i-H+1<<" "<<j-W+1<<endl; */
		    a[k].push_back({i-H,j-W,s[i][j]});
		}
	    }
	}
	tp[k][0]=[&]{
	for(auto [x,y,c]:a[k])if(x<0)return 0;
	    return 1;
	}();
	tp[k][1]=[&]{
	for(auto [x,y,c]:a[k])if(y>=W)return 0;
	    return 1;
	}();
	tp[k][2]=[&]{
	for(auto [x,y,c]:a[k])if(x>=H)return 0;
	    return 1;
	}();
	tp[k][3]=[&]{
	for(auto [x,y,c]:a[k])if(y<0)return 0;
	    return 1;
	}();
	/* cout<<tp[k][0]<<" "<<tp[k][1]<<" "<<tp[k][2]<<" "<<tp[k][3]<<endl; */
    }
    for(int i=1;i<=K*H;i++)for(int j=1;j<=K*W;j++)res[i][j]='.';
    cout<<n*W<<" "<<n*H<<endl;
    dfs(1,1);
}

