#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x){
        for(f=1; !isdigit(c); c=gc()) if(!(c^45)) f=-1;
        for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
        return *this;
    }
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

int n, pos[N], a[N], f[N], len;

int main() {
    io >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        io >> x; pos[x] = i;
    } 
    for (int i = 1; i <= n; i++) {
        int x;
        io >> x; a[i] = pos[x];
    }
    
    for (int i = 1; i <= n; i++) {
        if (f[len] < a[i]) f[++len] = a[i];
        else {
            int l = 0, r = len, res = 0;
            while (l <= r) {
                int mid = l+r >> 1;
                if (f[mid] > a[i]) res = mid, r = mid-1;
                else l = mid+1;
            }    
            f[res] = a[i];
        }
    }
    
    printf("%d", len);
    return 0;
}
