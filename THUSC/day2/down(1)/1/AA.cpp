#include<bits/stdc++.h>
using namespace std;
string s;
int len;
string remake(const string s){
    if(s=="")return s;
    int len=s.size(),i=0,j=len-1;
    while(i<len&&(s[i]==' '||s[i]=='\n'||s[i]=='\r'||s[i]=='\t'))i++;
    while(j>=0&&(s[j]==' '||s[j]=='\n'||s[j]=='\r'||s[j]=='\t'))j--;
    string t="";
    if(i>j)return "";
    else{
	for(int k=i;k<=j;k++)t+=s[k];
    }
    return t;
}
void div(string cur,int &ps,int ban){
    if(ps>=len)return;
    while(s[ps]!='<')++ps;
    /* cout<<"tiaoshi!!! "<<ps<<" "<<cur<<" "<<ban<<"tiaoshiwanle!!! "<<endl; */
    string type="";
    ps++;
    while(s[ps]!=' '&&s[ps]!='>')type+=s[ps],++ps;
    while(s[ps]!='>')++ps;
    /* cout<<"taipu "<<type<<endl; */
    if(type=="img")return;
    else if(type=="style"||type=="script"){
	ban|=1;
	while(!(s[ps]=='/'&&s[ps+1]=='s'))++ps;
	if(ps>=len)return;
	while(s[ps]!='>')++ps;
	if(ps>=len)return;
	return;
    }
    if(cur!="")cur=cur+">"+type;
    else cur=type;
    ++ps;
    for(;;++ps){
	if(s[ps]=='<'){
	    if(s[ps+1]=='/'){
		while(s[ps]!='>')++ps;
		return;
	    }
	    else{
		div(cur,ps,ban);
	    }
	}
	else{
	    string ans="";
	    /* cout<<"find "<<s[ps]<<endl; */
	    while(s[ps]!='<')ans+=s[ps],ps++;
	    ps--;
	    if(!ban){
		/* cout<<ans<<endl; */
		ans=remake(ans);
		if(ans!="")cout<<cur+":"+ans<<endl;
	    }
	}
    }
}
int main(){
    string t;
    while(getline(cin,t)){
	s+=t;
    }
    len=s.size()+5;
    s+="          ";
    int pos=0;
    div("",pos,0);
}
