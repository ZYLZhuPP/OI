#include<bits/stdc++.h>
using namespace std;

const int N = 2e3 + 5;

template<class C> inline bool chkmax(C &x, const C &y) {return x<y? x=y, 1: 0;}

struct IO {
    char c, f;
#define gc() getchar()
    template<class C>
    inline IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc(); x *= f; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int n, k;
long double a[N], b[N], f[N][N/2], g[N][N/2], ans = 0;

int main() {
    io >> n >> k;
    for (int i = 1; i <= n; ++i) {
        scanf("%Lf", &a[i]);
    }
    
    sort(a + 1, a + n + 1);
    
    f[0][0] = 1;
    for (int i = 1; i <= k; ++i) {
        f[i][0] = f[i - 1][0] * (1 - a[i]);
        for (int j = 1; j <= k/2; ++j) f[i][j] = a[i] * f[i - 1][j - 1] + (1 - a[i]) * f[i - 1][j];
    }
    
    for (int i = 1; i <= k; ++i) b[i] = a[n - i + 1];
    
    g[0][0] = 1;
    for (int i = 1; i <= k; ++i) {
        g[i][0] = g[i - 1][0] * (1 - b[i]);
        for (int j = 1; j <= k/2; ++j) g[i][j] = b[i] * g[i - 1][j - 1] + (1 - b[i]) * g[i - 1][j];
    }
    
    for (int i = 0; i <= k; i++) {
        long double res = 0;
        for (int j = 0; j <= k/2 && j <= i; j++) {
            res += f[i][j] * g[k - i][k/2 - j];
        }
        chkmax(ans, res);
    }
    
    printf("%.10Lf", ans);
    return 0;
} 

