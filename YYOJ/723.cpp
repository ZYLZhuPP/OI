#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;

char a[N];
int la,p[N],bo;

int main(){
    scanf("%d", &la);
    scanf("%s", a);
    p[0]=0;
    int j=0;
    for(int i=1; i<la; i++){
        while(j && a[i]^a[j]) j=p[j-1];
        if(a[i]==a[j]) j++;
        p[i]=j;
    }
    bo=la-p[la-1];
    printf("%d\n", bo);
    return 0;
}
