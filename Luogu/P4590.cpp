#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 20, M = 1005, S = (1 << 15) + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, int y) { x = mo(x + y); }

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
    inline IO& operator >> (char *x) {
        while ((c = gc()) < 33 && ~c);
        while (c > 32) *x++ = c, c = gc();
        *x = 0; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int t, n, m, fa[N], fb[N], cnt[S], to[S << 2][4];
int f[2][S << 2], a[N], ans[N];
char st[N];

int encode(const int *a, int p) {
    int s = 0;
    For (i, 1, n) s = s << 1 | (a[i] - a[i - 1]);
    return (s << 2) + p;
}
void decode(int *b, int s) {
    rFor (i, n, 1) b[i] = s & 1, s >>= 1;
    For (i, 1, n) b[i] += b[i - 1];
}

namespace init {
    void _cnt() { For (i, 1, S - 1) cnt[i] = cnt[i ^ (i & -i)] + 1; }
    void _to() {
        For (x, 0, (1 << n) - 1) {
            For (p, 0, 2) {
                int s = (x << 2) + p;
                decode(fa, x);
                For (k, 0, 2) {
                    int y = (p == k)? p + 1: !k;
                    if (y == 3) { to[s][k] = -1; continue; }
                    For (i, 1, n) {
                        fb[i] = max(fa[i], fb[i - 1]);
                        if (k == a[i]) fb[i] = max(fb[i], fa[i - 1] + 1);
                    }
                    to[s][k] = encode(fb, y);
                }
            }
        }
    }
}

void solve() {
    memset(f, 0, sizeof f);
    int *f0 = f[0], *f1 = f[1];
    f1[0] = 1;
    For (i, 1, m) {
        swap(f0, f1);
        For (x, 0, (1 << n) - 1) {
            For (p, 0, 2) {
                int s = (x << 2) + p;
                For (k, 0, 2) if (~to[s][k]) add(f1[to[s][k]], f0[s]);
                f0[s] = 0;
            }
        }
    }

    memset(ans, 0, sizeof ans);
    For (x, 0, (1 << n) - 1) 
        For (p, 0, 2) {
            int s = (x << 2) + p;
            add(ans[cnt[x]], f1[s]);
        }
}

int main() {
    init::_cnt();
    io >> m >> n;
    io >> (st + 1);
    For (i, 1, n) a[i] = st[i]=='N'? 0: st[i]=='O'? 1: 2;
    init::_to();
    solve();
    For (i, 0, n) printf("%d\n", ans[i]);

    return 0;
}
