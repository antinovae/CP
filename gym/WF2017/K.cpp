#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,q,nxt[maxn],id[maxn];
char s[20][maxn];
vector<int> bord[20];
void kmp(int m,char s[]) {
    nxt[0]=-1;nxt[1]=0;
    for(int i=2;i<=m;i++){
        nxt[i]=nxt[i-1];
	while(nxt[i]!=-1&&s[nxt[i]+1]!=s[i])nxt[i]=nxt[nxt[i]];
        nxt[i]++;
    }   
}

int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=q;i++){
	scanf("%s",s[i]+1);id[i]=i;
	int m=strlen(s[i]+1);kmp(m,s[i]);
	/* for(int i=1;i<=m;i++){ */
	/*     cout<<nxt[i]<<" "; */
	/* } */
	/* cout<<endl; */
	for(int j=m;j>=1;j=nxt[j]){
            if(j>=m*2-n){
		/* cout<<i<<' '<<j<<endl; */
		bord[i].push_back(j);}
        }
    }
    sort(id+1,id+1+q,[](int i,int j){return bord[i]==bord[j]?i<j:bord[i]<bord[j];});
    for(int i=1;i<=q;i++){
        printf("%s\n",s[id[i]]+1);
    }
    return 0;
}
