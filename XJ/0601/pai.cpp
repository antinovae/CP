#include<bits/stdc++.h>
using namespace std;
int n,m;
mt19937 rnd(114514);
void make(){
    FILE *f=fopen("in","w");
    fprintf(f,"%d\n",n);
    for(int i=2;i<=n;i++){
	fprintf(f,"%d %d\n",i,(int)(rnd()%(i-1)+1));
    }
    fprintf(f,"%d\n",n);
    for(int i=1;i<=n;i++){
	fprintf(f,"%d\n",(int)(rnd()%n+1));
    }
    fclose(f);
}
int main(){
    n=10000;
    for(int i=1;i<=100;i++){
	cerr<<"test "<<i<<" : ";
	make();
	system("./B < in > out");
	system("./std < in > ans");
	if(system("diff out ans")){
	    puts("WA");return 0;
	}
	else{
	    puts("AC");
	}
    }
}

