#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 305;
const ll INF = 1e14;
inline void cmin(ll &x, const ll &y) { y<x? x=y: 0; }

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
    inline bool operator ~ () { return ~c; }
} io;

int n, m, o, on[4] = {1, 1, 1, 1}, x[N], y[N], pos[N], a[N];
ll f[N][N][N], g[N][N][N], ans, w[4][N];

int main() {
    memset(w, 31, sizeof w);
    io >> n >> m;
    For (i, 1, m) io >> a[i];
    x[0] = y[0] = 1;
    memset(f, 31, sizeof f); memset(g, 31, sizeof g);
    f[0][0][0] = 0;
    For (p, 1, m) {
        int op;
        io >> op;
        if (op == 2) {
            int x;
            io >> x;
            on[x] ^= 1;
        }
        For (i, 1, 3) For (j, 0, p) cmin(w[i][j], on[i]? a[p]: INF);
        if (op == 1) {
            pos[++o] = p;
            For (i, 0, o - 1) For (j, 0, o - 1) swap(g[o - 1][i][j], f[o - 1][i][j]), swap(g[i][o - 1][j], f[i][o - 1][j]), swap(g[i][j][o - 1], f[i][j][o - 1]);
            io >> x[o] >> y[o];
            ll d = 1ll * abs(x[o] - y[o]) * a[p];
            For (i, 0, o) For (j, 0, o) f[o][i][j] = f[i][o][j] = f[i][j][o] = INF;
            //memset(f, 31, sizeof f);
            //ans = INF;
            For (i, 0, o - 1) For (j, 0, o - 1) if ((!i && !j) || i ^ j) {
                if (i == o - 1 || j == o - 1) {
                    For (k, 0, max(0, o - 2)) if (((!i && !k) || i ^ k) && ((!k && !j) || k ^ j)) {
                        if (on[1]) cmin(f[o][i][j], g[k][i][j] + w[1][pos[k]] * abs(y[k] - x[o]) + d);
                        if (on[2]) cmin(f[i][o][j], g[i][k][j] + w[2][pos[k]] * abs(y[k] - x[o]) + d);
                        if (on[3]) cmin(f[i][j][o], g[i][j][k] + w[3][pos[k]] * abs(y[k] - x[o]) + d);
                    }
                    continue;
                }
                if (on[1]) cmin(f[o][i][j], g[o - 1][i][j] + w[1][pos[o - 1]] * abs(y[o - 1] - x[o]) + d);
                if (on[2]) cmin(f[i][o][j], g[i][o - 1][j] + w[2][pos[o - 1]] * abs(y[o - 1] - x[o]) + d);
                if (on[3]) cmin(f[i][j][o], g[i][j][o - 1] + w[3][pos[o - 1]] * abs(y[o - 1] - x[o]) + d);
                //cmin(ans, min(f[o][i][j], min(f[i][o][j], f[i][j][o])));
            }
        }
    }
    ans = o? INF: 0;
    For (i, 0, o - 1) For (j, 0, o - 1) if ((!i && !j) || i ^ j) cmin(ans, min(f[o][i][j], min(f[i][o][j], f[i][j][o])));
    printf("%lld", ans);

    return 0;
}