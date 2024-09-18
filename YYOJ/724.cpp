#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;

char a[N];
int la,p[N];
long long ans;

int main(){
    scanf("%d", &la);
    scanf("%s", a+1);
    p[1]=0;
    int j=0;
    for(int i=2; i<=la; i++){
        while(j && a[i]^a[j+1]) j=p[j];
        if(a[i]==a[j+1]) j++;
        p[i]=j;
    }
    for(int i=2; i<=la; i++){
        int j=i;
        while(p[j]) j=p[j];
        if(p[i]) p[i]=j;
        ans+=i-j;
    }
    printf("%lld\n", ans);
    return 0;
}
