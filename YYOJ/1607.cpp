#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 5e6 + 5;

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n;
ll a[N], mi, ans;

int main() {
    io >> n;
    for (int i = 1; i <= n; ++i) {
        io >> a[i];
        if (a[i] == 0) {
            puts("0");
            return 0;
        }
        if (a[i] == 1) {
            ans += mi + 1;
            mi = 0;
        } else {
            if (mi) ans += a[i] * a[i - 1], mi = min(mi, a[i]);
            else mi = a[i];
        }
    }
    
    printf("%lld", ans + mi);
    
    return 0;
} 
