#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e5 + 5;

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

int n, m, a[N], b[N], stk[N], top, fa[N][20], s[N][20];

int main() {
    io >> n >> m;
    For (i, 1, n) {
        io >> a[i] >> b[i];
        while (top && a[stk[top]] < a[i]) fa[stk[top]][0] = i, s[stk[top]][0] = b[i], top--;
        stk[++top] = i;
    }
    For (j, 1, 19) For (i, 1, n) fa[i][j] = fa[fa[i][j - 1]][j - 1], s[i][j] = s[i][j - 1] + s[fa[i][j - 1]][j - 1];
    int k, x;
    while (m--) {
        io >> k >> x;
        if (x > b[k]) {
            x -= b[k];
            rFor (i, 19, 0) if (x > s[k][i]) x -= s[k][i], k = fa[k][i];
            k = fa[k][0];
        }
        printf("%d\n", k);
    }

    return 0;
}