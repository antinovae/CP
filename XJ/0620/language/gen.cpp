#include <bits/stdc++.h>
using namespace std;
const int N=410;
vector<tuple<int,int,int>>ans;
int n,a[N][N],m;
mt19937 rnd(0);
void gen(){
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=rnd()%n+1;
}

int main() {
    freopen("language.in","w",stdout);
    scanf("%d%d",&n,&m);
    cout<<n<<" "<<m<<endl;
    gen();
    for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
	    cout<<a[i][j]<<" ";
	}
	cout<<endl;
    }
} 
