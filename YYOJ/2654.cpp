#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int n, q, ls[N], rs[N], sz[N], dfn[N], ed1[N], ed2[N], tim, f[N];
int B, be[N], bl[320], br[320], s[N], S[320], mk[320], co[N], Co[320], f1[320][N], f2[320][N];

inline int query(int x) {
    int b = be[x], res = 0;
    For (i, 1, b - 1) res += S[i];
    For (i, bl[b], x) res += s[i];
    return res;
}

inline int solve(int u) {
    int res = 1 + f[u];
    if (mk[be[u]]) co[u] = Co[be[u]];
    if (co[u] == 0) res += sz[ls[u]];
    if (co[u] == 1) res += sz[u] - 1;
    int x = dfn[u];
    For (i, 1, B) if (mk[i]) {
        if (Co[i] == -1) res += f1[i][x];
        if (Co[i] == 0) res += f2[i][x];
    }
    return res + query(x);
}

inline void add(int x, int d) { s[x] += d; S[be[x]] += d; }

inline void up(int x, int d) {
    if (co[x] == -1) add(dfn[x] + 1, d), add(ed2[x] + 1, -d);
    if (co[x] == 0) add(ed1[x] + 1, d), add(ed2[x] + 1, -d);
}

inline void upd(int l, int r, int x) {
    int i = be[l];
    if (mk[i]) {
        For (j, bl[i], br[i]) co[j] = Co[i], up(j, 1);
        mk[i] = 0;
    }
    For (j, l, r) up(j, -1), co[j] = x, up(j, 1);
}

inline void Upd(int l, int r, int x) {
    int L = be[l], R = be[r];
    if (L == R) return upd(l, r, x);
    For (i, L + 1, R - 1) {
        if (!mk[i]) {
            For (j, bl[i], br[i]) up(j, -1);
            mk[i] = 1;
        }
        Co[i] = x;
    }
    upd(l, br[L], x); upd(bl[R], r, x);
}

inline void dfs0(int u) {
    if (!u) return;
    dfn[u] = ++tim; sz[u] = 1;
    f[ls[u]] = f[u]; dfs0(ls[u]); sz[u] += sz[ls[u]]; ed1[u] = tim;
    f[rs[u]] = f[u] + sz[ls[u]]; dfs0(rs[u]); sz[u] += sz[rs[u]]; ed2[u] = tim;
}

int main() {
    io >> n >> q; B = sqrt(n);
    For (i, 1, B) bl[i] = br[i - 1] + 1, br[i] = i * B, mk[i] = 1, Co[i] = -1;
    br[B] = n; For (i, 1, B) For (j, bl[i], br[i]) be[j] = i;
    For (i, 1, n) io >> ls[i] >> rs[i], co[i] = -1;
    dfs0(1);
    For (i, 1, n) {
        int b = be[i];
        f1[b][dfn[i] + 1]++; f1[b][ed2[i] + 1]--;
        f2[b][ed1[i] + 1]++; f2[b][ed2[i] + 1]--;
    }
    For (i, 1, B) For (j, 1, n) f1[i][j] += f1[i][j - 1], f2[i][j] += f2[i][j - 1];
    int op, l, r, x;
    while (q--) {
        io >> op;
        if (op == 1) io >> l >> r >> x, Upd(l, r, x);
        else io >> x, printf("%d\n", solve(x));
    }

    return 0;
}
