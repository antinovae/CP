#include<bits/stdc++.h>
using namespace std;
const int maxn=10001;
int n,b[maxn],a[maxn];
int check(int x){
    for(int i=1;i<=n;i++){
	b[i]=a[i];
    }
    int cur=x;
    for(int i=1;i<=n&&cur>=1;cur--){
	if(b[i]<cur)return 0;
	b[i]-=cur;
	if(b[i]==0)i++;
    }
    if(cur)return 0;
    cur=x;
    for(int i=n;i>=1&&cur>=1;cur--){
	if(b[i]<cur)return 0;
	b[i]-=cur;
	if(b[i]==0)i--;
    }
    if(cur)return 0;
    return 1;
}
int main(){
    scanf("%d",&n);
    int m=0,sum=0;
    for(int i=1;i<=n;i++){
	scanf("%d",&a[i]);
	m=max(m,a[i]);
	sum+=a[i];
    }
    if(sum&1){
	puts("no quotation");
    }
    else if(sum==2){
	puts("1");
    }
    else{
	int ans=0;
	for(int i=2;i<=m;i++){
	    if(check(i))ans=i;
	}
	if(!ans){
	    puts("no quotation");
	}
	else {
	    printf("%d\n",ans);
	}
    }
}
