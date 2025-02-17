#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 5e5 + 5;

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

int n, h[N];
double f[N], sq[N];

double F(int i, int j) { return sq[i - j] + h[j] - h[i]; }

void solve(int l, int r, int x, int y) {
    if (l > r) return;

    int m = (l + r) >> 1, pos = m;
    double ma = 0;
    For (i, x, min(m - 1, y)) if (F(m, i) > ma) ma = F(m, i), pos = i;
    f[m] = max(f[m], ma);

    solve(l, m - 1, x, pos); solve(m + 1, r, pos, y);
}

int main() {
    io >> n;
    For (i, 1, n) sq[i] = sqrt(i);
    For (i, 1, n) io >> h[i];

    solve(1, n, 1, n);
    For (i, 1, n >> 1) swap(h[i], h[n - i + 1]), swap(f[i], f[n - i + 1]);
    solve(1, n, 1, n);
    For (i, 1, n >> 1) swap(f[i], f[n - i + 1]);

    For (i, 1, n) printf("%d\n", (int)ceil(f[i]));

    return 0;
}
