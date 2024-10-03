#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 1e6 + 5, Mo = 1e9 + 7;
inline int mo(int x) { return x -= x>=Mo? Mo: x<0? -Mo: 0; }

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

int n, m, a[N], ans = 1, vis[N];

int main() {
    io >> n >> m;
    For (i, 0, (1 << m) - 1) io >> a[i];
    For (i, 0, (1 << m) - 1) {
        int x = a[i];
        if (vis[x]) {
            int k = i & -i;
            For (j, 0, k - 1) if (a[i - k + j] ^ a[i + j]) return puts("0"), 0;
            ans = mo(ans + ans);
            i += k - 1;
        } else vis[x] = 1;
    }
    For (i, 1, n) if (!vis[i]) ans = 0;
    printf("%d", ans);

    return 0;
}
