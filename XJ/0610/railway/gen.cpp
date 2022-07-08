#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int n,m,Q;
void make(){
    int n=100,m=30,Q=100;
    cout<<n<<" "<<m<<" "<<Q<<endl;
    for(int i=1;i<=n;i++){
	cout<<rnd()%m+1<<' ';
    }
    puts("");
    for(int i=1;i<n;i++){
	cout<<i+1<<' '<<rnd()%i+1<<" "<<rnd()%n+1<<endl;
    }
    puts("");
    for(int i=1;i<=Q;i++){
	int x=rnd()%2+1;
	cout<<x<<' ';
	if(x==1){
	    int x=rnd()%n+1,y=rnd()%m+1;
	    cout<<x<<' '<<y<<endl;
	}
	else{
	    int x=rnd()%m+1;
	    cout<<x<<endl;
	}
    }
}
int main(){
    make();
}
