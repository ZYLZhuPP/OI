#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll P = 1e6 + 3;
const int N = 2e3 + 5; 

struct IO {
    static const int BufS=1<<21;
    char buf[BufS], *S, *T, c, f;
#define gc() ((S==T && (T=(S=buf)+fread(buf, 1, BufS, stdin)), S==T)? EOF: *S++)
    template<class C>
    inline IO& operator >> (C &x){
        for(f=1; !isdigit(c); c=gc()) f|=-!(c^45);
        for(x=0; isdigit(c); c=gc()) x=(x<<3)+(x<<1)+(c^48); x*=f;
        return *this;
    }
    inline bool operator ~ (){while(c<33 && c^EOF) c=gc(); return c^EOF;}
}io;

struct Node {
    ll x, y;
    bool operator < (const Node & X) const{
        return  x ^ X.x? x < X.x: y < X.y;  
    }
} a[N];

ll f[N];
ll n, m, K;
ll fac[P], invfac[P];

ll qPow(ll a, ll b) {
    ll res = 1;
    for (; b; b >>= 1, a = a * a % P)
        if (b & 1)
            res = res * a % P;
    return res;
}

ll C(ll n, ll m) {
    if (m > n) return 0;
    if (n >= P)
        return C(n / P, m / P) * C(n % P, m % P) % P;
    return fac[n] * invfac[m] % P * invfac[n - m] % P;
}

void init() {
    fac[0] = 1;
    for (ll i = 1; i < P; ++i)
        fac[i] = fac[i - 1] * i % P;
    invfac[P - 1] = qPow(fac[P - 1], P - 2);
    for (ll i = P - 1; i; --i)
        invfac[i - 1] = invfac[i] * i % P;
}

int main() {
    init();
    io >> n >> m >> K;
    for (int i = 1; i <= K; ++i)
        io >> a[i].x >> a[i].y;
    
    sort(a + 1, a + K + 1);
    a[++K] = {n + 1, m + 1};
    
    for (ll i = 1; i <= K; ++i) {
        f[i] = C(a[i].y - 1, a[i].x - 1);
        for (ll j = 1; j < i; ++j)
            if (a[j].y < a[i].y) {
                f[i] -= f[j] * C(a[i].y - a[j].y - 1, a[i].x - a[j].x - 1) % P;
                (f[i] < 0) && (f[i] += P);
            }
    }
    
    printf("%lld", f[K]);
}
