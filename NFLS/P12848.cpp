#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2505;

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

namespace BIT {
    int o[N];
#define lowbit(x) ((x) & -(x))
    inline void upd(int x) { for (; x < N; x += lowbit(x)) o[x]++; }
    inline int query(int x) { int r = 0; for (; x; x -= lowbit(x)) r += o[x]; return r; }
}
using namespace BIT;

int n, q, s[N], nxt[N], pre[N], ans[N][N];
vector<array<int, 2 > > qs[N << 1];
char a[N];

int main() {
    freopen("bracket.in", "r", stdin);
    freopen("bracket.out", "w", stdout);
    io >> n >> q;
    scanf("%s", a + 1);
    For (i, 1, n) s[i] = s[i - 1] + (a[i]=='('? 1: -1);
    s[n + 1] = -1e9; For (i, 0, n) for (nxt[i] = i; s[nxt[i]] >= s[i]; ++nxt[i]);
    s[0] = -1e9; For (i, 1, n) for (pre[i] = i; s[pre[i]] >= s[i]; --pre[i]);
    s[0] = 0; For (i, 1, n) For (j, i, n) qs[s[j] - s[i - 1] + n].pb({i, j});
    For (i, 0, 2 * n) {
        memset(o, 0, sizeof o);
        for (auto &[l, r] : qs[i]) upd(l);
        for (auto &[l, r] : qs[i]) ans[l][r] = query(nxt[l - 1]) - query(l - 1);
        memset(o, 0, sizeof o);
        vector<int > qr[n + 1];
        for (auto &[l, r] : qs[i]) qr[r].pb(l);
        rFor (r, n, 1) {
            for (auto &l : qr[r]) ans[l][r] -= query(nxt[l - 1]) - query(l - 1);
            for (auto &l : qr[r]) upd(l);
        }
        memset(o, 0, sizeof o);
        vector<array<int, 2 > > qp[n + 1];
        for (auto &[l, r] : qs[i]) qp[pre[r]].pb({l, r});
        For (p, 1, n) {
            for (auto &[l, r] : qp[p]) ans[l][r] -= query(nxt[l - 1]) - query(l - 1);
            for (auto &l : qr[p]) upd(l);
        }
    }
    int l, r;
    while (q--) io >> l >> r, printf("%d\n", ans[l][r]);

    fclose(stdin); fclose(stdout);
    return 0;
}
