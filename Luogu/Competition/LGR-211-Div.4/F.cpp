#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 105;
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

int n, m, t, K, T1 = -1, T2 = -1, T3 = -1, T4 = -1, vis[N][N], lst[N];

int main() {
    io >> n >> m >> t >> K;
    int x, y, z;
    For (i, 1, n) {
        io >> x >> y >> z;
        if (z) {
            T1 = x;
            if (!vis[x][y]) {
                lst[x] = i;
                T2 = x;
                vis[x][y] = 1;
                if (!vis[x][0]++) T4 = x;
            }
        }
    }
    int t0 = 0;
    For (i, 1, m) if (vis[i][0] < K && cmax(t0, lst[i])) T3 = i;
    printf("%d %d %d %d", T1, T2, T3, T4);

    return 0;
}
