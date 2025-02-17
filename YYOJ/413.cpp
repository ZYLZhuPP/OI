#include<bits/stdc++.h>
using namespace std;

char a[10], b[10];

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    inline IO& operator >> (char *x){
        while(c<33) c=gc();
        for(; c>32; c=gc()) (*x++)=c;
        return *this;
    }
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

void dfs(int l, int r, int L, int R){
    if(L>R) return;
    int Rt=L, rt=l, mid=L;
    while(a[rt]^b[Rt]) rt++, mid++;
    dfs(l, rt-1, Rt+1, mid);
    dfs(rt+1, r, mid+1, R);
    putchar(b[Rt]);
}

int main(){
    io>>a>>b;
    dfs(0, strlen(a)-1, 0, strlen(b)-1);
    return 0;
} 
