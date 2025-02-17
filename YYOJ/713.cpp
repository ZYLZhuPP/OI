#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

const int N=1e6+5;
const ull P=79;

int l;
ull p[N],f[N];
char st[N];

void init(){
    p[0]=1;
    for(int i=1; i<=N; i++) p[i]=p[i-1]*P;
}

bool ok(int k){
    ull pd=f[k];
    for(int i=1; i<l/k; i++){
        if((f[i*k+k]-f[i*k]*p[k])^pd) return 0;
    }
    return 1;
}

int main(){
    init();
    while(~scanf("%s", st+1) && st[1]^'.'){
        memset(f, 0, sizeof(f));
        l=strlen(st+1);
        for(int i=1; i<=l; i++) f[i]=f[i-1]*P+st[i];
        for(int i=1; i<=l; i++)if(!(l%i)){
            if(ok(i)){
                printf("%d\n", l/i);
                break;
            }
        }
    }
    return 0;
} 
