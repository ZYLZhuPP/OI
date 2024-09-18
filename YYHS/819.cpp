#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5, Mo = 1e9 + 9;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }
inline int ml(int x, int y) { return 1ll * x * y % Mo; }
inline void mul(int &x, int y) { x = ml(x, y); }

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

int n, m, l[N], r[N], pos[N], t, _2 = 1;
vector<int > to[N];

namespace tr {
    int o[N << 2], tagm[N << 2], tagd[N << 2];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    void mark(int p, int t, int d) {
        mul(o[p], t); add(o[p], d);
        mul(tagm[p], t); mul(tagd[p], t); add(tagd[p], d);
    }
    void pushdown(int p) {
        if (!tagm[p]) tagm[p] = 1;
        if (tagm[p] ^ 1 || tagd[p]) {
            mark(ls, tagm[p], tagd[p]);
            mark(rs, tagm[p], tagd[p]);
            tagm[p] = 1; tagd[p] = 0;
        }
    }
    void pushup(int p) { o[p] = mo(o[ls] + o[rs]); }
    void upd(int p, int l, int r, int x, int y, int t, int d) {
        if (r < x || y < l) return;
        if (x <= l && r <= y) return mark(p, t, d);
        M; pushdown(p); upd(goL, x, y, t, d); upd(goR, x, y, t, d);
        pushup(p);
    }
    int query(int p, int l, int r, int x) {
        if (l == r) return o[p];
        M; pushdown(p); return x<=m? query(goL, x): query(goR, x);
    }
}

int main() {
    io >> n >> m;
    For (i, 1, n) {
        io >> l[i] >> r[i];
    }
    pos[1] = 0;
    For (i, 1, m) io >> pos[i + 1];
    sort(pos + 1, pos + m + 2);
    t = unique(pos + 1, pos + m + 2) - pos - 1;
    pos[t + 1] = Mo;

    For (i, 1, n) {
        l[i] = lower_bound(pos + 1, pos + t + 2, l[i]) - pos;
        r[i] = upper_bound(pos + 1, pos + t + 2, r[i]) - pos - 1;
        if (l[i] <= r[i]) to[r[i]].push_back(l[i]); else mul(_2, 2);
    }

    tr::upd(1, 1, t, 1, 1, 1, 1);
    For (i, 1, t) {
        for (auto &l : to[i]) {
            int d = tr::query(1, 1, t, l - 1);
            tr::upd(1, 1, t, 1, l - 1, 2, 0);
            tr::upd(1, 1, t, l, i, 1, d);
        }
    }

    printf("%d", ml(tr::query(1, 1, t, t), _2));

    return 0;
}
