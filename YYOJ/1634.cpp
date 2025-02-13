#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
template<class C> inline bool chkmin(C &x, const C &y) { return x>y? x=y, 1: 0; }
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
	inline IO& operator >> (char &x) {
	    while ((c = gc()) < 33 && ~c);
	    x = c; return *this;
	}
	inline bool operator ~ () {return ~c;}
} io;

int n, q, op, l, r, x, y, ans;
char a[N];

struct mat {
    int v[2][2];
    mat() { memset(v, 0, sizeof(v)); }
    mat(char c) {
        if (c == '0') v[0][0] = 0, v[1][1] = v[0][1] = v[1][0] = 1;
        else if (c == '1') v[0][0] = v[0][1] = v[1][0] = 1, v[1][1] = 0;
        else memset(v, 31, sizeof(v));
    }
    mat operator + (const mat &x) const {
        mat res('I');
        For (k, 0, 1) For (i, 0, 1) For (j, 0, 1) 
            chkmin(res.v[i][j], v[i][k] + x.v[k][j]);
        return res;
    }
};

namespace tr {
    mat o[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    void pushup(int p) { o[p] = o[ls] + o[rs]; }
    void build(int p, int l, int r) {
        if (l == r) { o[p] = mat(a[l]); return; }
        M; build(goL); build(goR);
        pushup(p);
    }
    void upd(int p, int l, int r, int x) {
        if (l == r) { o[p] = mat(a[x]); return; }
        M; x<=m? upd(goL, x): upd(goR, x);
        pushup(p);
    }
    mat query(int p, int l, int r, int x, int y) {
        if (x <= l && r <= y) return o[p];
        M; return m+1>y? query(goL, x, y): m<x? query(goR, x, y): (query(goL, x, y) + query(goR, x, y));
    }
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    tr::build(1, 1, n);

    io >> q;
    while (q--) {
        io >> op;
        if (op == 1) {
            io >> l >> r;
            mat res = tr::query(1, 1, n, l, r);
            ans = min(min(res.v[0][0], res.v[0][1] + 1), min(res.v[1][0] + 1, res.v[1][1] + 2));
            printf("%d\n", ans);
        } else {
            io >> x >> y;
            a[x] = '0' + y;
            tr::upd(1, 1, n, x);
        }
    }

    return 0;
}
