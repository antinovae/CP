#include<bits/stdc++.h>
using namespace std;
int main(){
    for(int i=1;i<=100;i++){
	cout<<i<<" : ";
	system("./gen > in");
	system("./railway < in >out");
	system("./brute < in >ans");
	if(system("diff out ans")){
	    puts("WA");
	    exit(0);
	}
	puts("AC");

    }
}
