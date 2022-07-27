#include<bits/stdc++.h>
using namespace std;
const int N=1000;
int n,m,Q;
vector<int>c;
mt19937 rnd(0);
void make(){
    FILE *f=fopen("in","w");
    c.resize(0);
    for(int i=1;i<=n;i++)c.push_back(i);
    shuffle(c.begin(),c.end(),rnd);
    fprintf(f,"%d\n",n);
    for(int i=0;i<n;i++){
	    fprintf(f,"%d ",c[i]);
    }
    fprintf(f,"\n");
    fprintf(f,"%d\n",Q);
    for(int i=1;i<=n;i++){
	for(int j=i;j<=n;j++)
	fprintf(f,"%d %d\n",i,j);
    }
    fclose(f);
}
int main(){
    n=1000,Q=n*(n+1)/2;
    for(int i=1;i<=100;i++){
	printf("test %d :",i);
	make();
	system("./I < in > out");
	system("./std < in > ans");
	/* system("cat in"); */
	/* system("cat out"); */
	/* system("cat ans"); */
	if(system("diff out ans")){
	    puts("WA");return 0;
	}
	puts("AC");

    }

}
