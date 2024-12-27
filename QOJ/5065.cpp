#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 5e3 + 5;

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

int T, n;
char s[N];
int g[N][N];
ll f[N][N], ans;

int main() {
    io >> T;
    while (T--) {
        ans = 0;
        scanf("%s", s + 1);
        n = strlen(s + 1);
        For (i, 0, n + 1) For (j, 0, n + 1) g[i][j] = f[i][j] = 0;
        rFor (i, n, 1) rFor (j, n, 1) if (s[i] == s[j]) g[i][j] = g[i + 1][j + 1] + 1;
        For (i, 1, n) {
            For (j, 1, i - 1) if (g[i][j] >= (i - j)) f[i][i - j]++;
            For (j, 1, n) f[i][j] += f[i][j - 1];
            For (j, 1, n) f[i][j] += f[i][j - 1];
        }
        For (i, 2, n) For (j, i + 3, n) if (g[i][j] >= 2) ans += f[i][min(j - i - 1, g[i][j]) - 1];
        printf("%lld\n", ans);
    }
    return 0;
}