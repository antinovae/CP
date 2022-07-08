#include<bits/stdc++.h>
using namespace std;
mt19937 rnd(time(0));
int f[1001][1001];
int main(){
    int n=100;
    for(int i=1;i<=n;i++){
	for(int j=1;j<i;j++){
	    f[i][j]=(rnd()%10==0);

	    f[j][i]=f[i][j]^1;
	}
    }
    cout<<n<<' '<<2<<endl;
    for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
	    cout<<f[i][j]<<' ';
	}
	    cout<<endl;
    }
}
