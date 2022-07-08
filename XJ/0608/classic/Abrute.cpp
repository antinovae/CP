#include<bits/stdc++.h>
using namespace std;
const int maxn=1000001;
int n,a[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
	scanf("%d",&a[i]);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
	for(int j=1;j<=n;j++){
	    ans+=(a[i]&a[j])*(a[i]|a[j])*(a[i]^a[j]);
	}
    }
    cout<<ans<<endl;
}
