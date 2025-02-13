#include<bits/stdc++.h>
using namespace std;

#define pb emplace_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;

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
	inline bool operator ~ () const { return ~c; }
} io;

int n, m;

inline ll range(const int &l, const int &r, const int &x, const int &y) { return min(r, y) - max(l, x) + 1; }
namespace Seg {
    const int S = N * 890, C = 2;
    int tot = 0;
    struct Node {
        int c[C];
        Node() { memset(c, 0, sizeof c); }
    } o[S];
    ll s[S], t[S];
    void upd(int &p, int l, int r, const int &x, const int &y, const int &d) {
//    cout << l << r << endl;
        if (!d || r < l || l > y || r < x) return;
//        cout << l << r << p << endl;
        if (!p) p = ++tot;
        s[p] += range(l, r, x, y) * d;
        if (x <= l && r <= y) return void(t[p] += d);
        int m = ceil(1.f * (r - l + 1) / C);
        For (i, 0, C - 1) upd(o[p].c[i], l + i * m, min(l + (i + 1) * m - 1, r), x, y, d);
//        cout << "ls = " << ls << endl; cout << "p = " << p << endl;
    }
    ll query(int p, int l, int r, const int &x, const int &y) {
        if (!p || r < l || l > y || r < x) return 0;
//        cout << l << r << " " << o[p].s << endl;
        if (x <= l && r <= y) return s[p];
        ll res = range(l, r, x, y) * t[p];
        int m = ceil(1.f * (r - l + 1) / C);
        For (i, 0, C - 1) res += query(o[p].c[i], l + i * m, min(l + (i + 1) * m - 1, r), x, y);
        return res;
    }
}

namespace BIT {
#define lowbit(x) ((x) & -(x))
    int rt1[N], rt2[N];
    inline void upd(int x, int X, const int &y, const int &Y, const int &d) {
        for (int k = x; k <= n; k += lowbit(k)) Seg::upd(rt1[k], 1, m, y, Y, d), Seg::upd(rt2[k], 1, m, y, Y, 1ll * x * d);
        for (int k = ++X; k <= n; k += lowbit(k)) Seg::upd(rt1[k], 1, m, y, Y, -d), Seg::upd(rt2[k], 1, m, y, Y, -1ll * X * d);
    }
    inline ll pre(int x, const int &l, const int &r) {
        ll res = 0;
        for (int k = x; k; k -= lowbit(k)) res += 1ll * Seg::query(rt1[k], 1, m, l, r);
        res *= x + 1;
        for (int k = x; k; k -= lowbit(k)) res -= 1ll * Seg::query(rt2[k], 1, m, l, r);
        return res;
    }
    inline ll query(int x, int X, const int &y, const int &Y) {
        return pre(X, y, Y) - pre(x - 1, y, Y);
    }
}
using namespace BIT;
    
/*namespace Seg_Seg {
    struct Node {
        int s, t;
        Node() { s = t = 0; }
    } o[N << 1];
    inline void upd(const int &x, const int &X, const int &y, const int &Y, const int &d) {
        int l = x + n - 1, r = X + n + 1, sz = 1, L = 0, R = 0;
        for (; l ^ r ^ 1; l >>= 1, r >>= 1, sz <<= 1) {
            Seg::upd(o[l].s, 1, m, y, Y, 1ll * L * d);
            Seg::upd(o[r].s, 1, m, y, Y, 1ll * R * d);
            if (~l & 1)
                Seg::upd(o[l ^ 1].s, 1, m, y, Y, 1ll * sz * d),
                Seg::upd(o[l ^ 1].t, 1, m, y, Y, d), L += sz;
            if (r & 1)
                Seg::upd(o[r ^ 1].s, 1, m, y, Y, 1ll * sz * d),
                Seg::upd(o[r ^ 1].t, 1, m, y, Y, d), R += sz;
        }
        for (; l; l >>= 1, r >>= 1)
            Seg::upd(o[l].s, 1, m, y, Y, 1ll * L * d),
            Seg::upd(o[r].s, 1, m, y, Y, 1ll * R * d);
    }
    inline ll query(const int &x, const int &X, const int &y, const int &Y) {
        ll res = 0;
        int l = x + n - 1, r = X + n + 1, sz = 1, L = 0, R = 0;
        for (; l ^ r ^ 1; l >>= 1, r >>= 1, sz <<= 1) {
            res += L * Seg::query(o[l].t, 1, m, y, Y);
            res += R * Seg::query(o[r].t, 1, m, y, Y);
            if (~l & 1) res += Seg::query(o[l ^ 1].s, 1, m, y, Y), L += sz;
            if (r & 1) res += Seg::query(o[r ^ 1].s, 1, m, y, Y), R += sz;
        }
        for (; l; l >>= 1, r >>= 1)
            res += L * Seg::query(o[l].t, 1, m, y, Y),
            res += R * Seg::query(o[r].t, 1, m, y, Y);
        return res;
    }
}*/

/*namespace Seg_Seg {        
#define ls p << 1
#define rs p << 1 | 1
    inline void upd(int p, int l, int r, const int &x, const int &X, const int &y, const int &Y, const int &d) {
        if (l > X || r < x) return;
        Seg::upd(o[p].s, 1, m, y, Y, range(l, r, x, X) * d);
        if (x <= l && r <= X) return Seg::upd(o[p].t, 1, m, y, Y, d);
        M; upd(goL, x, X, y, Y, d); upd(goR, x, X, y, Y, d);
    }
    inline ll query(int p, int l, int r, const int &x, const int &X, const int &y, const int &Y) {
        if (l > X || r < x) return 0;
        if (x <= l && r <= X) return Seg::query(o[p].s, 1, m, y, Y);
        M; return range(l, r, x, X) * Seg::query(o[p].t, 1, m, y, Y) + query(goL, x, X, y, Y) + query(goR, x, X, y, Y);
    }
}*/

int main() {
    io >> n >> m;
    int op;
    while (~(io >> op)) {
        int x, X, y, Y, d;
        if (op == 1) {
            io >> x >> y >> X >> Y >> d;
            upd(x, X, y, Y, d);
//            if (n > 2048 && (Seg::tot % (1 << 18) == 0)) cout << Seg::tot << endl;
        } else if (op == 2) {
            io >> x >> y >> X >> Y;
            printf("%lld\n", query(x, X, y, Y));
        }
    }
    return 0;
}
