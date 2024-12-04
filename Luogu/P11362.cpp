#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }
inline int qPow(int a, int b) { int r = 1; for (; b; mul(a, a), b >>= 1) if (b & 1) mul(r, a); return r; }

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

int T, n, m, V, f[N];
array<int, 2 > op[N];

int main() {
    io >> T;
    while (T--) {
        io >> n >> m >> V;
        For (i, 1, m) io >> op[i][0] >> op[i][1];
        sort(op + 1, op + m + 1);
        bool flag = 1;
        For (i, 2, m) if (op[i][0] == op[i - 1][0] && op[i][1] ^ op[i - 1][1]) flag = 0;
        m = unique(op + 1, op + m + 1) - op - 1;
        if (!flag) { puts("0"); continue; }
        f[1] = qPow(V, 2 * (op[1][0] - 1));
        For (i, 2, m) {
            int d = op[i][0] - op[i - 1][0];
            f[i] = ml(f[i - 1], mo(qPow(V, 2 * d) - ml(V - 1, qPow(V, d - 1))));
        }
        printf("%d\n", ml(f[m], qPow(V, 2 * (n - op[m][0]))));
    }

    return 0;
}
