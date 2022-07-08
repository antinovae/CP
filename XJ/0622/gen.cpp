#include<bits/stdc++.h>
using namespace std;
int main(){
    int n=2000,m=2*n-3;
    cout<<n<<" "<<m<<endl;
    for(int i=1;i<=n;i++){
	int x=rand()%n+1,y=rand()%n+1;
	cout<<x<<' '<<y<<endl;
    }
}
