#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e3 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

struct IO {
	char c; int f;
#define gc() (getchar())
	template<class C>
	inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
	}
	inline bool operator ~ () { return ~c; }
} io;

int n, V, K, ans, k[N], w[N], v[N], h[N], g[N], f[N], in[N];

inline void upd(int x, int f[]) {
    if (!k[x]) For (i, v[x], V) cmax(f[i], f[i - v[x]] + w[x]);
    else {
        int o = 1;
        while (o <= k[x]) {
            rFor (i, V, o * v[x]) cmax(f[i], f[i - o * v[x]] + o * w[x]);
            k[x] -= o;
            o <<= 1;
        }
        if (k[x]) rFor (i, V, k[x] * v[x]) cmax(f[i], f[i - k[x] * v[x]] + k[x] * w[x]);
    }
}

inline void solve() {
    memset(in, 0, sizeof in);
    memset(f, 224, sizeof f);
    f[0] = 0;
    For (i, 1, n) io >> k[i] >> w[i] >> v[i];
    io >> K;
    while (K--) {
        For (i, 0, V) g[i] = f[i];
        do {
            For (i, 0, V) h[i] = f[i];
            int x;
            io >> x;
            in[x] = 1;
            upd(x, h);
            For (i, 0, V) cmax(g[i], h[i]);
        } while (io.c == ' ');
        For (i, 0, V) cmax(f[i], g[i]);
    }
    For (i, 1, n) if (!in[i]) upd(i, f);
    if (f[V] < 0) puts("i'm sorry...");
    else printf("%d\n", f[V]);
}

int main() {
    while (~(io >> n >> V)) solve();

    return 0;
}
