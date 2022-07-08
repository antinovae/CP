#include<bits/stdc++.h>
using namespace std;
int n,m;
mt19937 rnd(0);
int make(){
    FILE *f=fopen("in","w");
    fprintf(f,"%d %d\n",n,m);
    for(int i=1;i<=n;i++){
	int x=rnd()%n+1;
	fprintf(f,"%d ",x);
    }
    fprintf(f,"\n");
    for(int i=1;i<=n;i++){
	int x=rnd()%2;
	if(x)fprintf(f,"A");
	else fprintf(f,"B");
    }
    fclose(f);

    
}
int main(){
    cin>>n>>m;
    make();
    for(int i=1;i<=100;i++){
	cout<<"test i: ";
	make();
	system("./G < in > out");
	system("./brute < in > ans");
	if(system("diff out ans")){
	    puts("WA");
	    return 0;
	}
    }

}
