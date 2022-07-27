#include<bits/stdc++.h>
using namespace std;
const int maxn=101;
mt19937 rnd(time(0));
int n,m;
int a[maxn][maxn];
void make(){
    FILE *f=fopen("in","w");
    fprintf(f,"%d\n",1);
    for(int i=1;i<=1;i++){
	fprintf(f,"%d %d\n",m,n);
	int indec=0;
	for(int i=1;i<=n;i++){
	    for(int j=1;j<=m;j++){
		a[i][j]=++indec;
	    }
	}
	for(int i=1;i<=100;i++){
	    if(rnd()%2==0){
		int x=rnd()%n+1;
		for(int i=1;i<=m/2;i++)swap(a[x][i],a[x][m-i+1]);
	    }
	    else{
		int x=rnd()%m+1;
		for(int i=1;i<=n/2;i++)swap(a[i][x],a[n-i+1][x]);
	    }
	}
	for(int i=1;i<=n;i++){
	    for(int j=1;j<=m;j++)fprintf(f,"%d ",a[i][j]);
	    fprintf(f,"\n");
	}
    }
    fclose(f);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=100;i++){
	make();
	printf("test %d : ",i);
	system("./A < in > out");
	if(system("diff out ans -Z"))return 0;
	puts("OK");
    }

}
