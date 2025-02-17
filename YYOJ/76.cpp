#include<bits/stdc++.h>
using namespace std;

const int N=1e6+5;

int n, a[N];

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
    inline IO& operator >> (char &x){
        while(c<33) c=gc(); x=c;
        return *this;
    }
    inline bool operator ~ (){return (f? c: c=gc())^EOF;}
}io;

int main(){
    io>>n;
    for(int i=1; i<=n; i++) io>>a[i];
    sort(a+1, a+n+1);
    for(int i=1; i<=n; i++) printf("%d ", a[i]);
    return 0;
} 
