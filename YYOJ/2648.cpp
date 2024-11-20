#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5;
template<class C> inline bool cmax(C &x, const C &y) { return y>x? x=y, 1: 0; }

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

int n, ss[N][26], st[N][26], f[N][N];
char s[N], t[N];

int main() {
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    n = strlen(s + 1);
    For (i, 1, n) {
        memcpy(ss[i], ss[i - 1], sizeof ss[i]); ss[i][s[i] - 'a']++;
        memcpy(st[i], st[i - 1], sizeof st[i]); st[i][t[i] - 'a']++;
    }
    For (i, 0, 25) if (ss[n][i] ^ st[n][i]) return puts("-1"), 0;
    memset(f, 224, sizeof f);
    f[0][0] = 0;
    For (i, 0, n) For (j, i, n) {
        cmax(f[i][j + 1], f[i][j]);
        if (s[i + 1] == t[j + 1]) cmax(f[i + 1][j + 1], f[i][j] + 1);
        if (st[j][s[i + 1] - 'a'] - ss[i][s[i + 1] - 'a']) cmax(f[i + 1][j], f[i][j]);
    }
    printf("%d", n - f[n][n]);

    return 0;
}
