#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (register int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (register int i = (r); i >= (l); --i)
template<class C> inline bool chkmax(C &x, const C &y) { return x<y? x=y, 1: 0; }
typedef long long ll;
const int N = 1005, M = 40325;

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

ll f[2][M], *f0, *f1, ans, g[N][M];
int l[N], r[N], m, tot, n, C[N], fac[10], cnt[1000];
bool vis[N];
int pu[M][8], to[M][8];

int lowbit(int x) { return x & -x; }

int getid(int a[]) {
    int res = 0, vis = (1 << m) - 1;
    For (i, 0, m - 1) res += cnt[vis & ((1 << a[i]) - 1)] * fac[m - i - 1], vis ^= 1 << a[i];
    return res;
}

void init() {
    cnt[0] = 0; For (i, 1, 1 << m) cnt[i] = cnt[i ^ lowbit(i)] + 1;
    fac[0] = 1; For (i, 1, m) fac[i] = fac[i - 1] * i;
    int a[m], b[M];
    For (i, 0, m - 1) a[i] = i;
    do {
        memcpy(pu[tot++], a, sizeof(a));
    } while (next_permutation(a, a + m));

    For (i, 0, tot - 1) {
        int t = 0;
        For (j, 0, m - 1) if (pu[i][j] > 0) a[t++] = pu[i][j] - 1;
        For (j, 0, m - 1) {
            memcpy(b, a, sizeof(a));
            rFor (k, m - 1, j + 1) b[k] = b[k - 1];
            b[j] = m - 1;
            to[i][j] = getid(b);
        }
    }
    f0 = f[0]; f1 = f[1];
}

inline bool in(int x, int y) { return l[x] <= y && y <= r[x] && x ^ y; }

ll get1(int x, int k) {
    ll res = 0;
    int l = x - m + 1, r = x;
    fill(vis + l, vis + r + 1, 0);
    For (i, 0, m - 1) {
        int c = l + pu[k][i];
        vis[c] = 1;
        For (j, l, r) if (!vis[j] && in(c, j)) res += C[c];
    }
    return res;
}

ll get2(int x, int k) {
    ll res = 0;
    int l = x - m + 1, r = x;
    fill(vis + l, vis + r + 1, 0);
    For (i, 0, m - 1) {
        int c = l + pu[k][i];
        vis[c] = 1;
        if (vis[r]) { if (in(r, c)) res += C[r]; }
        else { if (in(c, r)) res += C[c]; }
    }
    return res;
}

int main() {
    io >> n;
    For (i, 1, n) {
        io >> l[i] >> r[i] >> C[i];
        m = max(m, max(i - l[i] + 1, r[i] - i + 1));
    }

    init();

    For (i, 0, tot - 1) f1[i] = get1(m, i);
    For (i, m + 1, n) For (j, 0, tot - 1) g[i][j] = get2(i, j);
    For (i, m, n - 1) {
        swap(f0, f1);
        fill(f1, f1 + tot, 0);
        For (j, 0, tot - 1) {
            For (k, 0, m - 1) chkmax(f1[to[j][k]], f0[j] + g[i + 1][to[j][k]]);
        }
    }

    For (i, 0, tot - 1) chkmax(ans, f1[i]);

    printf("%lld", ans);

    return 0;
}
