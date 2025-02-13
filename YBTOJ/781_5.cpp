#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 4e5 + 5;

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

struct OP {
    int x, y, z, t, d, o;
    bool operator < (const OP &a) const { return x^a.x? x<a.x : y^a.y? y<a.y : z^a.z? z<a.z : t<a.t; }
} a[N], b[N], c[N];

int n, m, T, ans[N], op[N];

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void add(int x) { for (x++; x < N; x += lowbit(x)) o[x]++; }
    inline void del(int x) { for (x++; x < N; x += lowbit(x)) o[x] = 0; }
    inline int query(int x) { int r = 0; for (x++; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

inline void cdq2(int l, int r) {
    if (l == r) return;
    int m = (l + r) >> 1;
    cdq2(l, m); cdq2(m + 1, r);
    for (int i = l, j = l, k = m + 1; i <= r; ++i) {
        if (j <= m && (k > r || b[j].z <= b[k].z)) {
            c[i] = b[j++];
            if (c[i].o == 0 && op[c[i].t] == 1) add(c[i].t);
        } else {
            c[i] = b[k++];
            if (c[i].o == 1 && op[c[i].t] == 2) ans[c[i].t] += c[i].d * query(c[i].t);
        }
    }
    For (i, l, r) { b[i] = c[i]; if (c[i].o == 0 && op[c[i].t] == 1) del(c[i].t); }
}

inline void cdq1(int l, int r) {
    if (l == r) return;
    int m = (l + r) >> 1;
    cdq1(l, m); cdq1(m + 1, r);
    for (int i = l, j = l, k = m + 1; i <= r; ++i) {
        if (j <= m && (k > r || a[j].y <= a[k].y))
            b[i] = a[j++], b[i].o = 0;
        else b[i] = a[k++], b[i].o = 1;
    }
    For (i, l, r) a[i] = b[i];
    cdq2(l, r);
}

int main() {
    io >> T;
    while (T--) {
        m = 0;
        io >> n;
        For (i, 1, n) {
            ans[i] = 0;
            io >> op[i];
            if (op[i] == 1) {
                int x, y, z;
                io >> x >> y >> z;
                a[++m] = {x, y, z, i, 0, 0};
            } else {
                int X1, Y1, Z1, X2, Y2, Z2;
                io >> X1 >> Y1 >> Z1 >> X2 >> Y2 >> Z2;
                X1--; Y1--; Z1--;
                a[++m] = {X2, Y2, Z2, i, 1, 0};
                a[++m] = {X1, Y2, Z2, i, -1, 0};
                a[++m] = {X2, Y1, Z2, i, -1, 0};
                a[++m] = {X2, Y2, Z1, i, -1, 0};
                a[++m] = {X1, Y1, Z2, i, 1, 0};
                a[++m] = {X1, Y2, Z1, i, 1, 0};
                a[++m] = {X2, Y1, Z1, i, 1, 0};
                a[++m] = {X1, Y1, Z1, i, -1, 0};
            }
        }
        sort(a + 1, a + m + 1);
        cdq1(1, m);
        For (i, 1, n) if (op[i] == 2) printf("%d\n", ans[i]);
    }

    return 0;
}
