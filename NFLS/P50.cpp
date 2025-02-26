#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b = Mo - 2) { int r=1; for (;b;b>>=1,mul(a,a)) if (b&1) mul(r,a); return r; }

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

struct P {
    int a, b, c;
    inline P operator + (const P &r) const { return {mo(a + r.a), mo(b + r.b), mo(c + r.c)}; }
    inline P operator - (const P &r) const { return {mo(a - r.a), mo(b - r.b), mo(c - r.c)}; }
    inline P operator * (const ll &v) { return {a * v % Mo, b * v % Mo, c * v % Mo}; }
    inline int f(int x, int y) { return (1ll * a * x + 1ll * b * y + c) % Mo; }
} g[N][2], I = {0, 0, 1};

int n, c1, iv, sz[N], fa[N], f[N][2], inv[N], ans;
ll val[N];
char s[N];
vector<int > T[N];

inline void init() {
    inv[1] = 1; For (i, 2, N - 1) inv[i] = ml(Mo - Mo / i, inv[Mo % i]);
}

int main() {
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    init();
    io >> n;
    if(n == 2) return printf("%d", inv[2]), 0;
    scanf("%s", s + 1);
    For (i, 1, n) c1 += s[i] & 1;
    g[1][0] = {1, 0, 0}, g[1][1] = {0, 1, 0};
    g[2][1] = g[1][1] * ml(n, inv[n - 1]), g[2][0] = (g[1][0] * n - g[2][1] - I) * inv[n - 2];
    For (i, 2, n - 2) {
        g[i + 1][1] = (g[i][1] * n - I - g[i - 1][0] - g[i - 1][1] * (i - 1)) * inv[n - i];
        g[i + 1][0] = (g[i][0] * n - I - g[i + 1][1] - g[i - 1][0] * i) * inv[n - i - 1];
    }
    P E1 = g[n - 1][0] - g[1][1];
    P E2 = g[n - 1][1] - g[1][0];
    P E3 = E1 * E2.a - E2 * E1.a;
    f[1][1] = ml(Mo - E3.c, qPow(E3.b)), f[1][0] = (1ll * E2.b * f[1][1] + E2.c) % Mo * qPow(Mo - E2.a) % Mo;
    For (i, 2, n - 1) f[i][0] = g[i][0].f(f[1][0], f[1][1]), f[i][1] = g[i][1].f(f[1][0], f[1][1]);
    For (i, 2, n) io >> fa[i], T[fa[i]].pb(i);
    rFor (u, n, 1) { sz[u] = 1; for (auto &v : T[u]) sz[u] += sz[v], val[u] += val[v] + sz[v]; }
    For (u, 1, n) for (auto &v : T[u]) val[v] = val[u] + n - 2 * sz[v];
    For (i, 1, n) ans = (ans + val[i] % Mo * (f[c1][s[i] & 1] + inv[n])) % Mo;
    printf("%d", ml(ans, inv[n]));

    fclose(stdin); fclose(stdout);
    return 0;
}