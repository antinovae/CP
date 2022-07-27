#include<bits/stdc++.h>
using namespace std;
const int maxn=100001;
int n,m,a[maxn];
char s[maxn];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
	scanf("%d",&a[i]);
    }
    scanf("%s",s+1);
    for(int i=1;i<=m;i++){
	if(s[i]=='A'){
	    for(int j=1;j<=n;j++){
		if(a[j]<a[j-1])a[j]++;
	    }
	}
	else{
	    for(int j=n;j>=1;j--){
		if(a[j]<a[j+1])a[j]++;
	    }
	}
    }
    for(int i=1;i<=n;i++){
	cout<<a[i]<<" ";
    }
    cout<<endl;
}
