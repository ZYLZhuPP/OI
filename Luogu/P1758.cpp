#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 505, Mo = 1024523;
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
    inline bool operator ~ () { return ~c; }
} io;

int n, m, f[N][N], g[N][N];
char a[N], b[N];

int main() {
    scanf("%d%d", &n, &m);
    scanf("%s", a + 1); scanf("%s", b + 1);
    f[0][0] = 1;
    For (i, 0, n + m - 1) {
        swap(f, g); memset(f, 0, sizeof f);
        For (j, 0, min(n, i)) For (k, 0, min(n, i)) if (g[j][k]) {
            int x = g[j][k], a1 = n - j, a2 = n - k, b1 = m - i + j, b2 = m - i + k;
            if (a1 && a2 && a[a1] == a[a2]) add(f[j + 1][k + 1], x);
            if (a1 && b2 && a[a1] == b[b2]) add(f[j + 1][k], x);
            if (b1 && a2 && b[b1] == a[a2]) add(f[j][k + 1], x);
            if (b1 && b2 && b[b1] == b[b2]) add(f[j][k], x);
        }
    }
    printf("%d", f[n][n]);

    return 0;
}