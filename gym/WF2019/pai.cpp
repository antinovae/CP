#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,V;
mt19937 rnd(114514);
const int maxn=1e6+5;
int l[maxn],r[maxn],_l[maxn],_r[maxn];
void make(){
    FILE *f=fopen("in","w");
    int L=rnd()%V*100,R=rnd()%V*100;
    if(L>R)swap(L,R);
    fprintf(f,"%lld %lld %lld \n",L,R,n);
    for(int i=1;i<=n;i++){
	l[i]=rnd()%V;r[i]=rnd()%V;
	if(l[i]>r[i])swap(l[i],r[i]);
	_l[i]=i*100+(i*100-(V/2)+(rnd()%5-5))*l[i];
	_r[i]=i*100+(i*100-(V/2)+(rnd()%5-5))*r[i];
	fprintf(f,"%lld %lld %lld %lld\n",_l[i],l[i]*100,_r[i],r[i]*100);
    }
    /* for(int i=1;i<=n;i++){ */
	/* l[i]=rnd()%V;r[i]=rnd()%V; */
	/* if(l[i]>r[i])swap(l[i],r[i]); */
	/* _l[i]=i+(i-(V/2))*l[i]/100000; */
	/* _r[i]=i+(i-(V/2))*r[i]/100000; */
	/* fprintf(f,"%lld %lld %lld %lld\n",_l[i],l[i],_r[i],r[i]); */
    /* } */

    fclose(f);
}
signed main(){
    n=50,V=50;
    for(int i=1;i<=100;i++){
	cout<<"test "<<i<<" : ";
	make();
	system("./F < in > out");
	system("./std < in > ans");
	if(system("diff out ans")){
	    puts("WA");
	    exit(0);
	}
	else puts("AC");

    }
}
