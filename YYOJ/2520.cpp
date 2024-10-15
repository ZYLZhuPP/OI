#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int Mo = 998244353;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

struct mat {
    int o[61][61];
    mat() { memset(o, 0, sizeof o); }
    mat operator + (const mat &a) const {
        mat r;
        For (k, 0, 60) For (j, 0, 60) add(r.o[0][j], ml(o[0][k], a.o[k][j]));
        return r;
    }
    mat operator * (const mat &a) const {
        mat r;
        For (k, 0, 60) For (i, 0, 60) For (j, 0, 60) add(r.o[i][j], ml(o[i][k], a.o[k][j]));
        return r;
    }
} a[61], b[61], s[61];

int T;
ll n;

inline void init() {
    For (i, 0, 59) {
        For (j, 0, 60) {
            s[i].o[j][j] = 1;
            if (j <= i) s[i].o[j + 1][j] = 1;
        }
    }
    a[0] = b[0] = s[0];
    For (i, 1, 59) a[i] = b[i - 1] * s[i], b[i] = a[i] * b[i - 1];
}

int main() {
    init();
    io >> T;
    while (T--) {
        io >> n; n--;
        mat ans; For (i, 0, 60) ans.o[0][i] = 1;
        rFor (i, 59, 0) if (n >> i & 1) ans = ans + a[i];
        printf("%d\n", ans.o[0][0]);
    }

    return 0;
}
