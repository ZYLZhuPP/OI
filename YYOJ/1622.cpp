#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll Mo = 1e9 + 7;

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

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a % b);
}

ll A, B, C, D, ans;

int main() {
    io >> A >> B >> C >> D;
    
    for (int i = 1; i < 999; ++i) {
        for (int j = 1; j + i <= 999; ++j) if (gcd(i, j) == 1) {
            ll a = (A + i - 1) / i, b = B / i, c = (C + j - 1) / j, d = D / j;
            ll l = max(a, c), r = min(b, d);
            if (l <= r) ans = (ans + 1ll * (i + j) * (r - l + 1)) % Mo;
        }
    }
    
    printf("%lld", ans);
    
    return 0;
} 
