#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 2e5 + 5;

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

int n, m, c[N][20], dep[N], a[41];
ll s[41], ans[41];
bool on[N];

#define ls p << 1
#define rs p << 1 | 1

inline void up(int p) { dep[p] = max(on[ls] * dep[ls], on[rs] * dep[rs]) + 1; }

inline void init(int p) {
    if (p > n) return;
    c[p][1] = 1;
    init(ls); init(rs); up(p);
    memset(s, 0, sizeof s);
    For (i, 1, dep[p] - 1) s[i] = c[p][i + 1] = c[ls][i] + c[rs][i];
    For (i, 1, dep[ls]) For (j, 1, dep[rs]) s[i + j] += 1ll * c[ls][i] * c[rs][j];
    For (i, 1, 40) s[i] += s[i - 1], ans[i] += s[i];
}

inline void upd(int u, int v, int d) {
    up(u);
    For (i, 1, dep[v]) c[u][i + d] -= c[v][i];
    if (on[u]) upd(u >> 1, v, d + 1);
}

inline void pre(int u, int v, int d) {
    a[d]++;
    int x = v ^ 1;
    if (on[x]) For (i, 1, dep[x]) a[i + d] += c[x][i];
    if (on[u]) pre(u >> 1, u, d + 1);
}

int main() {
    io >> n >> m;
    For (i, 2, n) on[i] = 1;
    init(1);
    while (m--) {
        char op[3]; int u, x;
        scanf("%s", op);
        if (op[0] == '-') {
            io >> u; on[u] = 0;
            int v = u >> 1;
            upd(v, u, 1);
            memset(a, 0, sizeof a);
            pre(v, u, 0);
            memset(s, 0, sizeof s);
            For (i, 1, dep[u]) For (j, 0, 40 - i) s[i + j] += 1ll * c[u][i] * a[j];
            For (i, 1, 40) s[i] += s[i - 1], ans[i] -= s[i];
        } else {
            io >> x;
            printf("%lld\n", ans[x]);
        }
    }

    return 0;
}
