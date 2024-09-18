#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e9;

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
	inline IO& operator >> (char *x){
		while ((c = gc()) < 33 && ~c);
		while (c > 32) *x++ = c, c = gc();
		*x = 0; return *this;
	}
	int st[66], t;
#define pc(c) putchar(c)
    template<class C>
    inline IO& operator << (C x) {
        if (!x) pc('0'); if (x < 0) pc('-'), x = -x;
        while (x) st[++t] = x % 10, x /= 10;
        while (t) pc(st[t--] ^ 48);
        return *this;
    }
    inline IO& operator << (char x) {
        pc(x); return *this;
    }
	inline bool operator ~ () {return ~c;}
} io;

int q;
ll c, x, l, r, v;
char op[100];

namespace tr {
    struct Node {
        int l, r, m, v, s;
        Node (int l = 0, int r = 0, int m = 0, int v = 0, int s = 0):
            l(l), r(r), m(m), v(v), s(s) { }
    };
    vector<Node > o(2);
    int tot = 1;
#define ls o[p].l
#define rs o[p].r
#define M int m = (l + r) >> 1
#define me p, l, r
#define goL ls, l, m
#define goR rs, m + 1, r
    int get(int l, int r, int m, int v) { return (r - m + v) / v - (l-1 - m + v) / v; }
    void mark(int p, int l, int r, int m, int v) { o[p] = Node{ls, rs, m, v, get(l, r, m, v)}; }
    void chknew(int &p) { if (!p) p = ++tot, o.push_back(Node()); }
    void pushdown(int p, int l, int r) {
        chknew(ls); chknew(rs);
        if (o[p].v) { M; mark(goL, o[p].m, o[p].v); mark(goR, o[p].m, o[p].v); }
        o[p].v = 0;
    }
    void pushup(int p) { o[p].s = o[ls].s + o[rs].s; }
    void upd(int p, int l, int r, int x, int y, int mo, int v) {
        if (r < x || y < l) return;
        if (x <= l && r <= y) return mark(me, mo, v);
        pushdown(me); M; upd(goL, x, y, mo, v); upd(goR, x, y, mo, v);
        pushup(p);
    }
    ll pre(int p, int l, int r, int x) {
        if (!o[p].s) return INT_MIN;
        if (l == r) return l;
        pushdown(me); M; ll res = m+1<=x? pre(goR, x): INT_MIN;
        return res>INT_MIN? res: pre(goL, x);
    }
    ll suf(int p, int l, int r, int x) {
        if (!o[p].s) return INT_MAX;
        if (l == r) return l;
        pushdown(me); M; ll res = m>=x? suf(goL, x): INT_MAX;
        return res<INT_MAX? res: suf(goR, x);
    }
    void upd(int l, int r, int m, int v) { upd(1, 0, N, l, r, m, v); }
    ll pre(int x) { return pre(1, 0, N, x); }
    ll suf(int x) { return suf(1, 0, N, x); }
}

int main() {
    io >> q >> c;
    while (q--) {
        io >> op;
        if (op[0] == 'q') {
            io >> x;
            ll L = x - tr::pre(x), R = tr::suf(x) - x;
            ll ans = max(0ll, c - min(L, R) * min(L, R));
            io << ans << '\n';
        } else if (op[0] == 'c') {
            io >> l >> r >> v;
            tr::upd(l, r, l % v, v);
        } else {
            io >> l >> r;
            tr::upd(l, r, -1, N + 5);
        }
    }

    return 0;
}
