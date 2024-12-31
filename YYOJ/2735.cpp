#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, q, B, a[N], cnt[N], mx, tot, cnt1, ans[N];
vector<array<int, 3 > > qs[755];

inline void add(int i) {
    int x = a[i];
    cmax(mx, ++cnt[x]);
    if (cnt[x] == 1) tot++, cnt1++;
    else if (cnt[x] == 2) cnt1--;
}

int main() {
    io >> n >> q; B = sqrt(n);
    For (i, 1, n) io >> a[i];
    int l, r;
    For (i, 1, q) io >> l >> r, qs[l / B].pb({r, l, i});
    For (i, 0, B + 1) {
        int l = (i + 1) * B - 1, r = l;
        sort(qs[i].begin(), qs[i].end());
        for (auto &[y, x, id] : qs[i]) {
            while (r < y) add(++r);
            int mx_ = mx, tot_ = tot, cnt1_ = cnt1;
            rFor (j, min(l, y), x) add(j);
            int len = y - x + 1;
            if (mx >= (len + 1) / 2) ans[id] = tot>2||2*mx>len;
            else ans[id] = tot - (len&1? 0: cnt1);
            rFor (j, min(l, y), x) cnt[a[j]]--;
            mx = mx_, tot = tot_, cnt1 = cnt1_;
        }
        For (j, l + 1, r) cnt[a[j]] = 0;
        mx = tot = cnt1 = 0;
    }
    For (i, 1, q) printf("%d\n", ans[i]);

    return 0;
}
