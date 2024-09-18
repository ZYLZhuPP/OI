#include<bits/stdc++.h>
using namespace std;

const int N=15e3+5;

int len,p[N],ans,k;
char st[N];

void Kmp(char st[]){
    int len=strlen(st+1);
    p[1]=0;
    int j=0;
    for(int i=2; i<=len; i++){
        while(j && st[j+1]^st[i]) j=p[j];
        if(st[j+1]==st[i]) j++;
        p[i]=j;
    }
    for(int i=1; i<=len; i++){
         while(p[i]>k && p[p[i]]>=k) p[i]=p[p[i]];
         if((p[i]>=k) && ((p[i]<<1)+1<=i)) ans++;
    }
}

int main(){
    scanf("%s", st+1);
    len=strlen(st+1);
    scanf("%d", &k);
    for(int l=1; l<=len; l++) Kmp(st+l-1);
    printf("%d", ans);
    return 0;
}
