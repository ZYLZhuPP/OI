#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
const int N = 1e5 + 5, lgN = 20, H = 13;

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
    inline IO& operator >> (char &x){
        while ((c = gc()) < 33 && ~c);
        x = c; return *this;
    }
    inline bool operator ~ () const { return ~c; }
} io;

int h, n, p, q, ans, d, l, r, to[H][N], a[H][N], b[H][N][lgN];
char x;

int solve(int i, int l, int r) {
    if (to[i][l] > r) return 0;
    int res = 0, x = l;
    rFor (j, lgN - 1, 0) {
        if (b[i][x][j] <= r) x = b[i][x][j], res += 1 << j;
    }
    return res + 1;
}

int main() {
    io >> h >> n >> p >> q;
    For (i, 1, h) {
        For (j, 1, n) {
            io >> x;
            a[i][j] = x == 'X';
        }

        int r = n + 1;
        to[i][n + 1] = n + 1;
        rFor (j, n, 1) {
            if (a[i][j]) {
                to[i][j] = j;
                r = j;
            } else {
                to[i][j] = r;
            }
            b[i][j][0] = to[i][min(n + 1, to[i][j] + p)];

            For (k, 1, lgN - 1) {
                if (b[i][j][k - 1] == n + 1) b[i][j][k] = n + 1;
                else b[i][j][k] = b[i][b[i][j][k - 1]][k - 1];
            }
        }
    }

    while (q--) {
        ans = 0;
        io >> d >> l >> r;
        For (i, 1, d) ans += solve(i, l, r);
        printf("%d\n", ans);
    }

    return 0;
}
