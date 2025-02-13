#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
const int N = 3e5 + 5;

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
	inline bool operator ~ () {return ~c;}
} io;

int n, p[N], l[N], r[N];
ll ans;

struct Node {
    int m1, c1, m2, c2;
    Node (int m1 = N, int c1 = 0, int m2 = N, int c2 = 0): m1(m1), c1(c1), m2(m2), c2(c2) { }
    Node operator + (const int &x) const {
        return Node(m1 + x, c1, m2 + x, c2);
    }
    Node operator * (const Node &x) const {
        Node a = *this, b = x; if (a.m1 > b.m1) swap(a, b);
        if (a.m1 == b.m1) {
            a.c1 += b.c1;
            if (b.m2 < a.m2) a.m2 = b.m2, a.c2 = b.c2;
            else if (a.m2 == b.m2) a.c2 += b.c2;
        } else {
            if (b.m1 < a.m2) a.m2 = b.m1, a.c2 = b.c1;
            else if (a.m2 == b.m1) a.c2 += b.c1;
        }
        return a;
    }
    int count() const { return m2<=2? c1+c2: m1<=2? c1: 0; }
};

namespace tr {
    Node o[N << 2]; int tag[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    void mark(int p, int d) { o[p] = o[p] + d; tag[p] += d; }
    void pushdown(int p) { if (tag[p]) mark(ls, tag[p]), mark(rs, tag[p]), tag[p] = 0; }
    void pushup(int p) { o[p] = o[ls] * o[rs]; }
    void build(int p, int l, int r) {
        if (l == r) return o[p] = Node(0, 1), void();
        M; build(goL); build(goR);
        pushup(p);
    }
    void upd(int p, int l, int r, int x, int y, int d) {
        if (r < x || y < l) return;
        if (x <= l && r <= y) return mark(p, d);
        M; pushdown(p); upd(goL, x, y, d); upd(goR, x, y, d);
        pushup(p);
    }
    Node query(int p, int l, int r, int x) {
        if (r < x) return Node();
        if (x <= l) return o[p];
        M; pushdown(p); return query(goL, x) * query(goR, x);
    }
}

int main() {
    io >> n;
    For (i, 1, n) io >> p[i];
    For (i, 1, n) l[p[i]] = p[i - 1], r[p[i]] = p[i + 1];

    tr::build(1, 1, n);
    rFor (i, n, 1) {
        if (l[i] > r[i]) swap(l[i], r[i]);
        if (r[i] < i) tr::upd(1, 1, n, i, n, 1);
        else if (l[i] < i) tr::upd(1, 1, n, i, r[i] - 1, 1);
        else {
            tr::upd(1, 1, n, r[i], n, -1);
            tr::upd(1, 1, n, i, l[i] - 1, 1);
        }
        if (i < n) ans += tr::query(1, 1, n, i + 1).count();
    }

    printf("%lld", ans);

    return 0;
}
