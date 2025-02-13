#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long double Lf;
typedef pair<Lf, int > P;
const int N = 4e4 + 5, Mo = 39989, inf = 1e9;

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

int n, ans, tot;

namespace Seg {
    struct Line {
        Lf k, b; int id;
        Line(Lf k = -inf, Lf b = -inf, int id = 0): k(k), b(b), id(id) { }
    } o[N << 2];
    inline P F(const Line &v, const int &x) { return {v.k * x + v.b, -v.id}; }
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
#define I p, l, r
    inline void upd(int p, int l, int r, Line v) {
        M; if (F(v, m) > F(o[p], m)) swap(o[p], v);
        if (F(v, l) > F(o[p], l)) upd(goL, v);
        if (F(v, r) > F(o[p], r)) upd(goR, v);
    }
    inline void Upd(int p, int l, int r, int x, int y, Line v) {
        if (l > y || r < x) return;
        if (x <= l && r <= y) return upd(I, v);
        M; Upd(goL, x, y, v); Upd(goR, x, y, v);
    }
    inline P query(int p, int l, int r, int x) {
        if (l > x || r < x) return {-inf, 0};
        if (l == r) return F(o[p], x);
        M; return max(F(o[p], x), max(query(goL, x), query(goR, x)));
    }
}
using namespace Seg;

inline void add(int i, int x, int y, int X, int Y) {
    if (x == X) return Upd(1, 1, Mo, x, x, {0, max(y, Y), i});
    Lf k = 1.L * (Y - y) / (X - x), b = y - k * x;
    Upd(1, 1, Mo, x, X, {k, b, i});
}

int main() {
    io >> n;
    int op, x, y, X, Y;
    For (i, 1, n) {
        io >> op;
        if (op == 0) {
            io >> x; x = (x + ans - 1) % Mo + 1;
            printf("%d\n", ans = -query(1, 1, Mo, x).second);
        } else if (op == 1) {
            io >> x >> y >> X >> Y;
            x = (x + ans - 1) % Mo + 1, X = (X + ans - 1) % Mo + 1;
            y = (y + ans - 1) % inf + 1, Y = (Y + ans - 1) % inf + 1;
            if (x > X) swap(x, X), swap(y, Y);
            add(++tot, x, y, X, Y);
        }
    }

    return 0;
}
