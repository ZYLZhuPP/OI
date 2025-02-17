#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
typedef long double lf;
const int N = 125;

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

int n, m, d;
ll K, ans;

struct mat {
    lf o[N][N];
    mat() { memset(o, 0, sizeof o); }
    mat operator * (const mat &a) {
        mat r;
        For (i, 0, 3 * n) For (j, 0, 3 * n) For (k, 0, 3 * n) r.o[i][j] += o[i][k] * a.o[k][j];
        return r;
    }
} A, g[64];

int main() {
    io >> n >> m >> K; K += n;
    auto id = [](const int &i, const int &j) { return 3 * (i - 1) + j; };
    g[0].o[0][0] = 1;
    For (i, 1, n) A.o[0][id(i, 1)] = g[0].o[id(i, 3)][id(i, 2)] = g[0].o[id(i, 2)][id(i, 1)] = g[0].o[id(i, 1)][0] = 1;
    int u, v, w;
    For (i, 1, m) io >> u >> v >> w, g[0].o[id(u, 1)][id(v, w)]++;
    For (i, 1, 63) {
        g[i] = g[i - 1] * g[i - 1];
        if ((A * g[i]).o[0][0] >= K) { d = i; break; }
    }
    if (!d) { puts("-1"); return 0; }
    rFor (i, d, 0) {
        mat B = A * g[i];
        if (B.o[0][0] < K) A = B, ans |= 1ll << i;
    }
    printf("%lld", ans);

    return 0;
}
