#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
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

int T, n, a, b, c;

struct Node {
    int x, y, sx, sy, sy2, sxy;
    Node() { x = y = sx = sy = sy2 = sxy = 0; }
    inline Node operator * (const Node &a) const {
        Node r(a);
        add(r.x, x); add(r.y, y); add(r.sx, sx); add(r.sy, sy); add(r.sy2, sy2); add(r.sxy, sxy);
        add(r.sx, ml(x, a.x)); add(r.sy, ml(y, a.x));
        add(r.sy2, mo(ml(2, ml(y, a.sy)) + ml(a.x, ml(y, y))));
        add(r.sxy, mo(mo(ml(y, a.sx) + ml(x, a.sy)) + ml(a.x, ml(x, y))));
        return r;
    }
} X, Y;

inline Node qPow(Node a, int b) {
    Node r;
    while (b) {
        if (b & 1) r = r * a;
        a = a * a;
        b >>= 1;
    }
    return r;
}

inline Node ex_Euclid(int a, int b, int c, int n, const Node &X, const Node &Y) {
    if (!n) return Node();
    if (b >= c) return qPow(X, b / c) * ex_Euclid(a, b % c, c, n, X, Y);
    if (a >= c) return ex_Euclid(a % c, b, c, n, X, qPow(X, a / c) * Y);
    int m = (1ll * a * n + b) / c;
    return m? qPow(Y, (c - b - 1) / a) * X * ex_Euclid(c, (c - b - 1) % a, a, m - 1, Y, X) * qPow(Y, n - (1ll * c * m - b - 1) / a): qPow(Y, n);
}

int main() {
    X.y = 1; Y.x = Y.sx = 1;
    io >> T;
    while (T--) {
        io >> n >> a >> b >> c;
        Node ans = ex_Euclid(a, b, c, n, X, Y);
        printf("%d %d %d\n", mo(ans.sy + mo(b / c)), mo(ans.sy2 + ml(b / c, b / c)), ans.sxy);
    }

    return 0;
}
