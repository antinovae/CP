#include<bits/stdc++.h>
using namespace std;
int n;
int main(){
    freopen("another.in","r",stdin);
    freopen("another.out","w",stdout);
    scanf("%d",&n);
    string s,t;
    for(int i=0;i<n/2-2;i+=2)s+="01";
    s+="10";
    for(int i=n/2;i<n;i+=2)s+="01";
    for(int i=0;i<n/2;i+=2)t+="01";
    cout<<s<<endl<<t<<endl;
    return 0;
}

