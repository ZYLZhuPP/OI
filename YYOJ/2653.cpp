#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }

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

int n, m, x, a[N], b[N], f[N][N], s[N][N];

int main() {
    io >> n >> m;
    For (i, 1, n) io >> x, a[x]++;
    For (i, 1, m) b[i] = (a[i] % 3 - b[i - 1] - (i>1? b[i - 2]: 0) + 6) % 3;
    f[0][0] = 1; s[0][0] = 1;
    For (i, 2, m + 3) {
        For (j, 0, a[i - 2]) For (k, 0, a[i - 1]) {
            if (j % 3 != b[i - 2] || k % 3 != b[i - 1] || j + k > a[i - 1]) { f[j][k] = 0; continue; }
            f[j][k] = s[min(a[i - 1] - j - k, i>2? a[i - 3]: 0)][j];
        }
        For (j, 0, a[i - 2]) For (k, 0, a[i - 1]) s[j][k] = mo((j>0? s[j - 1][k]: 0) + f[j][k]);
    }
    printf("%d", f[0][0]);
    
    return 0;
}
