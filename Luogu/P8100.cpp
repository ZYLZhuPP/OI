#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e3 + 5, Mo = 1e9 + 7;
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

int T, n, cnt[2], f[N][N], pre[2][N], a[2][N];

int main() {
    a[0][0] = a[1][0] = -1;
    io >> T;
    while (T--) {
        cnt[0] = cnt[1] = 0;
        io >> n;
        int x;
        For (i, 1, n) {
            io >> x;
            int c = x & 1;
            a[c][++cnt[c]] = x;
            For (j, 0, cnt[!c]) if (abs(a[!c][j] - x) ^ 1) pre[c][cnt[c]] = j;
        }
        For (i, 0, cnt[0]) For (j, 0, cnt[1]) f[i][j] = 0;
        f[0][0] = 1;
        For (i, 0, cnt[0]) For (j, 0, cnt[1]) if (f[i][j]) {
            if (j >= pre[0][i + 1]) add(f[i + 1][j], f[i][j]);
            if (i >= pre[1][j + 1]) add(f[i][j + 1], f[i][j]);
        }
        printf("%d\n", f[cnt[0]][cnt[1]]);
    }

    return 0;
}
