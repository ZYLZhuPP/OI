#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int M = 2e7 + 5, Ps = 2e6 + 5;
const ll Mo = 998244353;

struct IO {
    char c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
}io;

ll n, m, B, ans, pw[100], pp[Ps];
int f[M], pri[Ps], mip[M], rest[M], psiz;

void Euler() {
    for (int i = 2; i < M; ++i) {
        if (!mip[i]) {
            pri[++psiz] = i;
            mip[i] = psiz;
            rest[i] = 1;
            ll a = i;
            while (!(B % a) && a <= m) a *= i;
            pp[psiz] = a / i; 
        }

        for (int j = 1; j <= psiz; ++j) {
            int p = pri[j], ne = i * p;
            if (ne >= M) break;
            mip[ne] = j;
            pri[ne] = j;
            if (j == mip[i]) {
                rest[ne] = rest[i];
                break;
            }
            rest[ne] = i;
        }
    }
}

ll qPow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = (res * a) % Mo;
        a = (a * a) % Mo;
        b >>= 1;
    }
    return res;
}

void init() {
    for (int i = 1; i <= 80; ++i) pw[i] = (qPow(i, n) - qPow(i - 1, n) + Mo) % Mo;
}

int main() {
    io >> n >> m >> B;
    Euler();
    init();
  
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= psiz; ++i) {
        for (ll j = 1, x = pri[i]; x <= m; ++j, x *= pri[i]) {
            for (ll k = 1, y = x; k <= j + 1; ++k, y /= pri[i]) 
                f[x] = (f[x] + pw[k] * min(pp[i], y) % Mo) % Mo;
        }
    }

    f[1] = ans = 1;
    for (int i = 2; i <= m; ++i) {
        f[i] = (ll)f[rest[i]] * f[i / rest[i]] % Mo;
        ans = (ans + f[i]) % Mo;
    }

    printf("%lld", ans);
    return 0;
}

