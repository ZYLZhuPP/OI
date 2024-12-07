#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;

int la,lb,p[N],pp[N],st[N],top;
char a[N],b[N];

void pre_kmp(){
    p[1]=0;
    int j=0;
    for(int i=2; i<=lb; i++){
        while(j && b[j+1]^b[i]) j=p[j];
        if(b[j+1]==b[i]) j++;
        p[i]=j;
    }
}

int main(){
    scanf("%s%s", a+1, b+1);
    la=strlen(a+1);
    lb=strlen(b+1);
    pre_kmp();
    for(int i=1; i<=la; i++){
        int j=pp[st[top]];
        st[++top]=i;
        while(j && b[j+1]^a[i]) j=p[j];
        if(b[j+1]==a[i]) j++;
        pp[i]=j;
        if(j==lb)
            top-=lb;
    }
    for(int i=1; i<=top; i++) putchar(a[st[i]]);
    return 0;
}
