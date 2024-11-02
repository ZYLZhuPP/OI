#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e4 + 5;
int Mo;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

int n, m, a[N], b[N], tot, l[N], r[N], no[N], mip[N], pri[N], psz;
ll c[N];

inline void init() {
    For (i, 2, N - 1) {
        if (!mip[i]) pri[mip[i] = ++psz] = i;
        For (j, 1, mip[i]) {
            if (pri[j] >= N / i) break;
            mip[i * pri[j]] = j;
        }
    }
}

inline bool check(int P) {
    Mo = P;
    l[0] = 1; For (i, 1, tot) l[i] = ml(l[i - 1], b[i] % Mo);
    r[tot + 1] = 1; rFor (i, tot, 1) r[i] = ml(r[i + 1], b[i] % Mo);
    int B = 0; For (i, 1, tot) add(B, ml(l[i - 1], r[i + 1]));
    int C = 1; For (i, 1, m) if (!no[i]) mul(C, c[i] % Mo);
    return B ^ C;
}

int main() {
    io >> n >> m;
    For (i, 1, n) io >> a[i];
    For (i, 1, m) io >> c[i];
    For (i, 1, n) For (j, 1, m) {
        if (a[i] == c[j]) { no[j] = 1; break; }
        else if (j == m) b[++tot] = a[i];
    }
    if (!tot) return puts("N"), 0;
    For (i, 1, tot) {
        Mo = b[i];
        int B = 1; For (j, 1, tot) if (i ^ j) mul(B, b[j] % Mo);
        int C = 1; For (j, 1, m) if (!no[j]) mul(C, c[j] % Mo);
        if (B ^ C) return puts("N"), 0;
    }
    init();
    For (i, 1, psz) if (check(pri[i])) return puts("N"), 0;
    puts("S");

    return 0;
}
