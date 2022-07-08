#include<bits/stdc++.h>
using namespace std;
const int maxn=4001,N=4000;
int n;
int st[maxn][maxn];
bool vis[maxn][maxn];
pair<int, int>c[maxn][maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
	char tp[3];int x,y,r;
	scanf("%s%d%d%d",tp,&x,&y,&r);
	x+=2000,y+=2000;
	if(tp[0]=='A'){
            c[x-(r/2)][y-(r/2)].first=max(c[x-(r/2)][y-(r/2)].first,r);
        }
        else{
            c[x-(r/2)][y].second=max(c[x-(r/2)][y].second,r/2);
        }
    }
    for(int i=0;i<=N;i++){
	for(int j=0;j<=N;j++){
            if(c[i][j].first){
		vis[i][j]=1;
                c[i][j+1].first=max(c[i][j+1].first,c[i][j].first-1);
                c[i+1][j].first=max(c[i+1][j].first,c[i][j].first-1);
                c[i+1][j+1].first=max(c[i+1][j+1].first,c[i][j].first-1);
            }
            if(c[i][j].second){
                st[i][j]|=1;
                st[i][j-1]|=2;
                st[i+1][j-1]|=4;
                st[i+1][j]|=8;
                c[i+1][j-1].second=max(c[i+1][j-1].second,c[i][j].second-1);
                c[i+1][j+1].second=max(c[i+1][j+1].second,c[i][j].second-1);
                c[i+2][j].second=max(c[i+2][j].second,c[i][j].second-1);
            }
        }
    }
    double ans=0;
    for(int i=0;i<=N;i++){
	for(int j=0;j<=N;j++){
            if(vis[i][j])ans++;
	    else if(st[i][j]){
		int bc=0;
		for(int k=0;k<4;k++)bc+=(st[i][j]>>k&1);
		if(bc==1)ans+=0.5;
                else{
                    if(((st[i][j]&1)&&(st[i][j]>>2&1))||((st[i][j]>>1&1)&&(st[i][j]>>3&1)))ans++;
                    else ans+=0.75;
                }
            }
        }
    }
    printf("%.2lf",ans);
}
