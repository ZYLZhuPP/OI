#include<bits/stdc++.h>
using namespace std;

const int N=2005;

char st[N];
long long len,di=1,n,mul,ans;

int main(){
    scanf("%s", st);
    len=strlen(st);
    if(isdigit(st[0])) mul=1;
    for(int pos=0; pos<len; pos++){
        if(st[pos]=='+') mul++;
        else if(st[pos]=='-') mul--;
        else if(st[pos]=='('){
            di=0;
            while(st[++pos]^')') di=di*10+(st[pos]^48);
        }else{
            n=st[pos]^48;
            while(isdigit(st[pos+1])) pos++, n=(n*10)+(st[pos]^48);
            ans+=mul*di*n;
            mul=0; di=1;
        }
    }
    printf("%lld", ans);
    return 0;
}//需要高精度 
