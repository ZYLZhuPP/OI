#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
typedef long long ll;
typedef vector<int > VI;
typedef vector<VI > VVI;
const int N = 15, Mo = 1e9 + 7;

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

int T, n, C, K, co[N], c[N];

inline int solve() {
    io >> n >> C >> K;
    For (i, 0, n - 1) io >> co[i] >> c[i];

    VI f(1 + 2 * K, 0); For (k, 0, K) f[k] = 1;
    VI vis; int j = 0;

    For (p, 0, n - 1) {
        int t = 0;
        for (; t < j && co[p] ^ vis[t]; t++);
        if (t == j) {
            j++;
            vis.pb(co[p]);
            For (k, 1, K) f.pb(f[K + k]);
        }

        int m = f.size();
        VVI a(m, VI(m, 0));
        a[0][0] = 1;

        For (k, 1, K) {
            a[k][k] = 1;
            For (x, 0, j - 1) if (x ^ t) a[k][(x + 2) * K + k] = 1;
            a[k][K + k] = C - j;

            if (j < C) {
                int u = K + k;
                a[u][u] = 1;
                a[u][k - 1] = 1;
                if (k > 1) {
                    For (y, 0, j - 1) a[u][(y + 2) * K + k - 1] = 1;
                    a[u][K + k - 1] = C - j - 1;
                }
            }

            For (x, 0, j - 1) {
                int u = (x + 2) * K + k;
                a[u][u] = 1;
                if (x ^ t) {
                    a[u][k - 1] = 1;
                    if (k > 1) {
                        For (y, 0, j - 1) if (y ^ x) a[u][(y + 2) * K + k - 1] = 1;
                        a[u][K + k - 1] = C - j;
                    }
                }
            }
        }

        for (int d = c[p]; d; d >>= 1) {
            if (d & 1) {
                VI g(m, 0);
                For (i, 0, m - 1) For (j, 0, m - 1) g[i] = (g[i] + 1ll * a[i][j] * f[j]) % Mo;
                f = g;
            }
            VVI b(m, VI(m, 0));
            For (i, 0, m - 1) For (j, 0, m - 1) For (k, 0, m - 1) b[i][j] = (b[i][j] + 1ll * a[i][k] * a[k][j]) % Mo;
            a = b;
        }
    }

    int res = (f[K] + 1ll * (C - j) * f[2 * K]) % Mo;
    For (x, 0, j - 1) res = (res + f[(x + 2) * K + K]) % Mo;
    return res;
}

int main() {
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
    printf("%d\n", solve());

    fclose(stdin); fclose(stdout);
    return 0;
}