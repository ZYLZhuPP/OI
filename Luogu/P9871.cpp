#include<bits/stdc++.h>
using namespace std;

#define mkp make_pair
#define st first
#define nd second
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e5 + 5;
template<class C> inline void clear(C &a) { C().swap(a); }

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

int c, T, n, m, k, x, y, l[N], r[N], pos[N << 1], t, v[N];
ll f[N << 1], d;
vector<pair<int, int> > to[N << 1];

namespace tr {
    ll o[N << 3], tag[N << 3];
#define ls p << 1
#define rs p << 1 | 1
#define M int m = (l + r) >> 1
#define goL ls, l, m
#define goR rs, m + 1, r
    void init() { memset(o, 0, sizeof(o)); memset(tag, 0, sizeof(tag)); }
    void mark(int p, ll d) { tag[p] += d, o[p] += d; }
    void pushdown(int p) { if (tag[p]) mark(ls, tag[p]), mark(rs, tag[p]), tag[p] = 0; }
    void pushup(int p) { o[p] = max(o[ls], o[rs]); }
    void upd(int p, int l, int r, int x, int y, ll d) {
        if (x <= l && r <= y) return mark(p, d);
        M; pushdown(p); if (m >= x) upd(goL, x, y, d); if (m + 1 <= y) upd(goR, x, y, d);
        pushup(p);
    }
    void upd(int p, int l, int r, int x, ll d) { upd(p, l, r, x, x, d); }
    ll query(int p, int l, int r, int x, int y) {
        if (x <= l && r <= y) return o[p];
        M; pushdown(p); return m<x? query(goR, x, y): m+1>y? query(goL, x, y): max(query(goL, x, y), query(goR, x, y));
    }
}

void init() {
    tr::init();
    t = 0;
}

int main() {
    io >> c >> T;
    while (T--) {
        init();
        io >> n >> m >> k >> d;
        For (i, 1, m) {
            io >> x >> y >> v[i];
            l[i] = x - y + 1, r[i] = x;
            pos[++t] = l[i], pos[++t] = r[i];
        }

        pos[0] = -1;
        sort(pos + 1, pos + t + 1);
        t = unique(pos + 1, pos + t + 1) - pos - 1;
        For (i, 1, t) clear(to[i]);
        For (i, 1, m) {
            l[i] = lower_bound(pos + 1, pos + t + 1, l[i]) - pos;
            r[i] = lower_bound(pos + 1, pos + t + 1, r[i]) - pos;
            to[r[i]].push_back(mkp(l[i], v[i]));
        }

        For (i, 1, t) {
            tr::upd(1, 1, t, i, (pos[i]-pos[i - 1]>1? f[i - 1]: f[i - 2]) - d);
            if (i > 1) tr::upd(1, 1, t, 1, i - 1, (-d) * (pos[i] - pos[i - 1]));
            for (auto &e : to[i]) tr::upd(1, 1, t, 1, e.st, e.nd);
            f[i] = max(f[i - 1], tr::query(1, 1, t, lower_bound(pos + 1, pos + t + 1, pos[i] - k + 1) - pos, i));
        }

        printf("%lld\n", f[t]);
    }

    return 0;
}
