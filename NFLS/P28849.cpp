#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, Mo = 1e9 + 7;
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

int n, a[N], l[N], r[N], ql[N], qr[N], hl, hr, tl, tr, sl[N], sr[N], S, Sl, Sr, ans, p;

inline int queryL(int x, int y) {
    int a = lower_bound(ql + hl, ql + tl + 1, x) - ql, b = upper_bound(ql + hl, ql + tl + 1, y) - ql - 1;
    if (a > b) return 1ll * (y - x) * l[ql[a]] % Mo;
    return (sl[b] - sl[a] + 1ll * (ql[a] - x) * l[ql[a]] + 1ll * (y - ql[b]) * l[ql[b + 1]]) % Mo;
}
inline int queryR(int x, int y) {
    int a = lower_bound(qr + hr, qr + tr + 1, x) - qr, b = upper_bound(qr + hr, qr + tr + 1, y) - qr - 1;
    if (a > b) return 1ll * (y - x) * r[qr[a]] % Mo;
    return (sr[b] - sr[a] + 1ll * (qr[a] - x) * r[qr[a]] + 1ll * (y - qr[b]) * r[qr[b + 1]]) % Mo;
}

int main() {
    freopen("unilobite.in", "r", stdin);
    freopen("unilobite.out", "w", stdout);
    io >> n;
    For (i, 1, n) io >> a[i];
    unordered_map<int, int > L, R;
    For (i, 1, n) l[i] = L.count(a[i])? L[a[i]]: 0, L[a[i]] = i;
    rFor (i, n, 1) r[i] = R.count(a[i])? R[a[i]]: n + 1, R[a[i]] = i;
    For (i, 1, n) cerr << l[i] << " " << r[i] << endl;
    S = Sl = Sr = 0; hl = hr = p = 1;
    For (i, 2, n - 1) {
        if (l[i] == i - 1 || l[i + 1] == i) { tl = hl - 1; tr = hr - 1; p = i; S = Sl = Sr = 0; continue; }
        int q = max(p, max(l[i] + 1, l[i + 1]));
        while (p < q) {
            int x = min(q, min(ql[hl], qr[hr])), L = l[ql[hl]], R = r[qr[hr]];
            add(S, -ml(x - p, ml(L, R))); add(Sl, -ml(x - p, L)); add(Sr, -ml(1ll * (p + x - 1) * (x - p) / 2 % Mo, R));
            p = x;
            if (p == ql[hl]) hl++;
            if (p == qr[hr]) hr++;
        }
        //cerr << p << " " << i << endl;
        ql[hl - 1] = qr[hr - 1] = p;
        while (hl <= tl && l[i] >= l[ql[tl]]) {
            int x = ql[tl], y = ql[tl - 1];
            add(Sl, -ml(x - y, l[x]));
            add(S, -ml(l[x], queryR(y, x)));
            tl--;
        }
        add(Sl, ml(i - ql[tl], l[i]));
        add(S, ml(l[i], queryR(ql[tl], i - 1)));
        ql[++tl] = i;
        sl[tl] = (sl[tl - 1] + 1ll * (i - ql[tl - 1]) * l[i]) % Mo;
        while (hr <= tr && r[i] <= r[qr[tr]]) {
            int x = qr[tr], y = qr[tr - 1];
            add(Sr, -ml(1ll * (x + y - 1) * (x - y) / 2 % Mo, r[x]));
            add(S, -ml(r[x], queryL(y, x)));
            tr--;
        }
        //cerr << S << endl;
        add(Sr, ml(1ll * (i + qr[tr] - 1) * (i - qr[tr]) / 2 % Mo, r[i]));
        add(S, ml(r[i], queryL(qr[tr], i)));
        //cerr << S << endl;
        qr[++tr] = i;
        sr[tr] = (sr[tr - 1] + 1ll * (i - qr[tr - 1]) * r[i]) % Mo;
        //cerr << S << " " << Sl << " " << Sr << endl;
        add(ans, Sr - S);
        add(ans, ml(i + 1, Sl));
        add(ans, -ml(i + 1, 1ll * (p + i - 1) * (i - p) / 2 % Mo));
        //cerr << ans << endl;
    }
    printf("%d", ans);

    fclose(stdin); fclose(stdout);
    return 0;
}
