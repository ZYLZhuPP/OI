#include<bits/stdc++.h>
using namespace std;

#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }
inline void add(int &x, const int &y) { x = mo(x + y); }
inline int ml(const int &x, const int &y) { return 1ll * x * y % Mo; }

struct IO {
    char c; int f;
#define gc() getchar()
    template<class C>
    IO& operator >> (C &x) {
        x = 0; f = 1;
        while (!isdigit(c = gc()) && ~c) f |= -!(c ^ 45);
        while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ 48), c = gc();
        x *= f; return *this;
    }
    bool operator ~ () const { return ~c; }
} io;

struct mat {
    int o[128][128];
    mat() { memset(o, 0, sizeof o); }
    mat operator + (const mat &a) const {
        mat r;
        For (i, 0, 127) For (j, 0, 127) r.o[i][j] = mo(o[i][j] + a.o[i][j]);
        return r;
    }
    mat operator * (const mat &a) const {
        mat r;
        For (k, 0, 127) For (i, 0, 127) For (j, 0, 127) add(r.o[i][j], ml(o[i][k], a.o[k][j]));
        return r;
    }
} A, B, ans, g[61];

ll n;
int m, cnt[61][101], f[128][128], Ans;

int main() {
    io >> n >> m;
    int x, y;
    For (i, 1, m) io >> x >> y, cnt[y][x]++;
    For (i, 0, 127) A.o[i][i] = ans.o[i][i] = f[i][i] = 1;
    For (i, 0, 127) {
        For (j, 0, 6) if (!(i % (1 << j))) {
            For (k, 1, min(100, i)) if (cnt[j][k]) {
                int x = i - k;
                For (l, 0, x) add(f[i][l], ml(cnt[j][k], f[x][l]));
            }
        }
    }
    For (i, 0, 127) {
        For (l, 0, i) if (f[i][l]) {
            For (j, 0, 6) if (!(l % (1 << j))) {
                For (k, l + 1, 100) if (cnt[j][k]) {
                    int x = 128 + l - k;
                    add(B.o[i][x], ml(cnt[j][k], f[i][l]));
                }
            }
        }
    }
    For (i, 7, 60) {
        mat X;
        For (j, 0, 127) For (k, 1, 100) if (cnt[i][k]) add(X.o[j][128 - k], ml(cnt[i][k], f[j][0]));
        g[i] = (i==7? B: g[i - 1] * g[i - 1]) + X * A;
        A = A * g[i];
        if (n >> i & 1) ans = ans * g[i];
    }
    n %= 128;
    For (i, 0, 127) add(Ans, ml(ans.o[n][i], f[i][0]));
    printf("%d", Ans);

    return 0;
}
