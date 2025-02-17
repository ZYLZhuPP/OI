#include<bits/stdc++.h>
using namespace std;

const int N=255;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x){
        for(f=1; !isdigit(c); c=gc()) if(!(c^'-')) f=-1;
        for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
        return *this;
    }
    inline IO& operator >> (char *x){
        while(c<33) c=gc();
        for(; c>32; c=gc()) (*x++)=c;
        return *this;
    }
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

char a[N];
int n,k,l;
bool flag;

int find(int l, int r){
    int res=l;
    for(int i=l+1; i<r; i++) if(a[i]<a[res]) res=i;
    return res;
}

int main(){
    io>>a>>k;
    n=strlen(a);
    k=n-k;
    while(k--){
        l=find(l, n-k);
        if(a[l]^'0' || flag || !k) putchar(a[l]), flag=1;
        l++;
    }
    return 0;
}
