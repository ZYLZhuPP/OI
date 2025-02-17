#include<bits/stdc++.h>
using namespace std;

const int N=1e3+5;

int n,h,a[N],ans;

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
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int main(){
    while(~io){
        io>>h;
        int *pos=lower_bound(a, a+ans, h);
        if(pos==a+ans) a[ans++]=h;
        else (*pos)=h;
    }
    printf("%d", ans);
    return 0;
}
