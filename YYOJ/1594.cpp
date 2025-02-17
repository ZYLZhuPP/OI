#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 5e5 + 5;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n;
ll x, ans, v[N];

int main() {
    io >> n;
    for (int i = 1; i <= n; ++i) io >> v[i];
    for (int i = n; i >= 1; --i) ans += (x = min(x + 1, v[i]));
    
    printf("%lld", ans);
    
    return 0;
} 
