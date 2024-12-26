#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }

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

int n, lB[N], lR[N], rR[N], rB[N], s[2][N], g[2][N], f[N];
char a[N];

inline int query(int k, int l, int r) {
    return l>r? 0: s[k][r] - (l? s[k][l - 1]: 0);
}

int main() {
    io >> n;
    scanf("%s", a + 1);
    For (i, 1, n) {
        if (a[i] == 'R') lR[i] = i, lB[i] = lB[i - 1];
        else if (a[i] == 'B') lB[i] = i, lR[i] = lR[i - 1];
        else lR[i] = lR[i - 1], lB[i] = lB[i - 1];
    }
    rR[n + 1] = rB[n + 1] = n + 1;
    rFor (i, n, 1) {
        if (a[i] == 'R') rR[i] = i, rB[i] = rB[i + 1];
        else if (a[i] == 'B') rB[i] = i, rR[i] = rR[i + 1];
        else rR[i] = rR[i + 1], rB[i] = rB[i + 1];
    }
    f[0] = s[0][0] = 1;
    For (i, 0, n) {
        if (a[i] == 'X') f[i] = f[i - 1];
        add(g[0][i], g[0][i - 1]); add(g[1][i], g[1][i - 1]);
        add(f[i], g[i & 1][i]);
        if (i > 0) {
            int R = lR[i], B = lB[i];
            if (R > B) add(f[i], query(i & 1, max(B, 2 * R - i), i - 1));
            else {
                add(f[i], query(i & 1, B, i - 1));
                if (R) {
                    int x = rB[R], y = lB[R];
                    add(f[i], query(i & 1, max(y, 2 * R - i), min(R - 1, 2 * x - i - 2)));
                }
            }
        }
        s[i & 1][i] = mo(s[i & 1][i - 1] + f[i]);
        s[!(i & 1)][i] = s[!(i & 1)][i - 1];
        if (i < n) {
            int R = rR[i + 1], B = rB[i + 1];
            if (B < R) {
                int x = min(2 * B - i - 1, R);
                add(g[i & 1][B], f[i]); add(g[i & 1][x], -f[i]);
            }
        }
    }
    printf("%d", f[n]);

    return 0;
}