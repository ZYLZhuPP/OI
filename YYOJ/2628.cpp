#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5, Mo = 1e9 + 7;
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

int n, K, x[N], f[N][N], g[N][N], ans;
vector<array<int, 2 > > F, G;

int main() {
    io >> n >> K;
    For (i, 1, n) io >> x[i];
    sort(x + 1, x + n + 1);
    f[0][0] = 1; F.pb({0, 0});
    For (i, 1, n) {
        for (auto &[a, b] : F) g[a][b] = f[a][b], f[a][b] = 0;
        swap(F, G); F.resize(0);
        int d = x[i] - x[i - 1];
        for (auto &[a, b] : G) {
            int a_ = a, b_ = b + a * d;
            if (b_ > K) continue;
            if (!f[a_][b_]) F.pb({a_, b_});
            add(f[a_][b_], ml(a + 1, g[a][b]));
            a_ = a + 1;
            if (!f[a_][b_]) F.pb({a_, b_});
            add(f[a_][b_], g[a][b]);
            if (!a) continue;
            a_ = a - 1;
            if (!f[a_][b_]) F.pb({a_, b_});
            add(f[a_][b_], ml(a, g[a][b]));
        }
    }
    For (i, 0, K) add(ans, f[0][i]);
    printf("%d", ans);

    return 0;
}
