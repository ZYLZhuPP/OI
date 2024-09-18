#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5;

int la,lb,p[N];
char a[N],b[N],ans;

void pre_kmp(){
    p[0]=0;
    int j=0;
    for(int i=1; i<lb; i++){
        while(j && b[i]^b[j]) j=p[j-1];
        if(b[i]==b[j]) j++;
        p[i]=j;
    }
}

void clear(){
    ans=0;
}

int main(){
    while(~scanf("%s", a)){
        la=strlen(a);
        if(a[0]=='#' && la==1) break;
        scanf("%s", b);
        lb=strlen(b);
        clear();
        pre_kmp();
        int j=0;
        for(int i=0; i<la; i++){
            while(j && a[i]^b[j]) j=p[j-1];
            if(a[i]==b[j]) j++;
            if(j==lb){
                ans++;
                j=0;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
