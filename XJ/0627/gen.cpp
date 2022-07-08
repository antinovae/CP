#include<bits/stdc++.h>
#include <random>
#include <utility>
using namespace std;
mt19937 rnd(0);
void make(){
    int n=100,m=100;
    int l=1,r=0;
    FILE *f=fopen("in","w");
    fprintf(f,"%d %d %d\n",n,m,3);
    for(int i=1;i<=n;i++){
	l=r+rnd()%3+1;
	r=l+rnd()%5+1;
	fprintf(f,"%d %d\n",l,r);
    }
    l=1,r=0;
    for(int i=1;i<=m;i++){
	l=r+rnd()%3+1;
	r=l+rnd()%5+1;
	fprintf(f,"%d %d\n",l,r);
    }
    fclose(f);
}
int main(){
    for(int i=1;i<=500;i++){
	cout<<"test "<<i<<" : ";
	make();
	system("./B < in > out");
	system("./std < in > ans");
	if(system("diff out ans")){
	    puts("WA!");
	    return 0;
	}
	puts("AC");
    }

    
    
}
