#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e3 + 5;
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

int T, n, m, Mx, p[N], pt[N][N], fa[N];
bitset<N > a[N], b[N], c[N];
bool flag;

inline int find(int x) { return x^fa[x]? fa[x] = find(fa[x]): x; }

int main() {
    io >> T;
    while (T--) {
        io >> n >> m;
        For (i, 1, m) {
            io >> p[i]; cmax(Mx, p[i]);
            a[i].reset();
            int x;
            For (j, 1, p[i]) io >> x, pt[i][j] = x, a[i][x] = 1;
        }
        if (Mx == 1) { puts("YES"); continue; }
        flag = 1;
        For (i, 1, min(n, 50)) if (flag) {
            For (j, 1, n) fa[j] = j, b[j].set();
            For (j, 1, m) if (!a[j][i]) For (k, 2, p[j]) fa[find(pt[j][k])] = find(pt[j][k - 1]);
            For (j, 1, m) if (a[j][i]) {
                For (k, 1, p[j]) {
                    int x = pt[j][k];
                    find(x); c[fa[x]][x] = b[fa[x]][x];
                }
                For (k, 1, p[j]) {
                    int x = pt[j][k];
                    b[fa[x]] = c[fa[x]];
                    if (!c[fa[x]].count()) flag = 0;
                }
                For (k, 1, p[j]) {
                    int x = pt[j][k];
                    c[fa[x]].reset();
                }
            }
        }
        puts(flag? "YES": "NO");
    }

    return 0;
}
