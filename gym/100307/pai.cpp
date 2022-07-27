#include<bits/stdc++.h>
using namespace std;
void make(int i,int j,int k,int l){
    FILE *f=fopen("in","w");
    fprintf(f,"%d %d %d %d\n",i,j,k,l);
    fclose(f);
}
int main(){
    int n=1,m=100;
    for(int i=1;i<=n;i++){
	for(int j=1;j<=m;j++){
	    for(int k=0;k<=i;k++){
		for(int l=0;l<=j;l++){
		    make(i,j,k,l);
		    printf("%d %d %d %d\n",i,j,k,l);
		    system("./I < in > out");
		    system("cat in");
		    /* system("cat out"); */
		    /* system("cat ans"); */
		    if(system("diff out ans"))return 0;
		}
	    }
	}
    }
}
