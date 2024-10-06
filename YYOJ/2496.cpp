#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 605, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }
inline void mul(int &x, const int &y) { x = ml(x, y); }

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

int T, n, fa[N], sz[N], a[N], f[N][N];
array<int, 2 > b[N];

inline int find(int x) { return x^fa[x]? fa[x] = find(fa[x]): x; }

int main() {
    io >> T;
    T = 3;
    while (T--) {
        io >> n;
        For (i, 1, n) fa[i] = i, sz[i] = 1;
        For (i, 1, n) {
            io >> a[i];
            For (j, 1, i - 1) {
                int x = sqrt(1ll * a[i] * a[j]);
                if (1ll * x * x ^ 1ll * a[i] * a[j]) continue;
                int u = find(i), v = find(j);
                if (u == v) continue;
                fa[v] = u; sz[u] += sz[v];
            }
        }
        For (i, 1, n) find(i), b[i] = {-sz[fa[i]], fa[i]};
        sort(b + 1, b + n + 1);
        memset(f, 0, sizeof f);
        int x = -b[1][0];
        f[x - 1][0] = 1;
        For (i, 2, x) mul(f[x - 1][0], i);
        int y = 0, J = x - 1;
        For (i, x + 1, n) {
            For (j, 0, J) rFor (k, y, 0) if (f[j][k]) {
                if (j) add(f[j - 1][k], ml(j, f[j][k]));
                if (y) add(f[j][k + 1], ml(2 * y - k, f[j][k]));
                mul(f[j][k], i - j - (2 * y - k)); 
            }
            if (b[i][1] ^ b[i + 1][1]) {
                rFor (j, J, 0) For (k, 1, y) if (f[j][k]) add(f[j + k][0], f[j][k]), f[j][k] = 0;
                y = 0; J += -b[i][0] - 1;
            } else y++;
        }
        printf("%d\n", f[0][0]);
    }

    return 0;
}
