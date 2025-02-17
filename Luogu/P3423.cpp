#include<bits/stdc++.h>
using namespace std;

#define For(i, l, r) for (int i = (l); i <= (r); ++i)
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
inline bool cmin(int &x, const int &y) { return y<x? x=y, 1: 0; }

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

int n, a[205], b[205], K, f[20005], who[20005], m, A[3005], B[3005], cnt[205], id[3005];
bool pre[20005][3005];

void solve(int i) {
    int x = b[i], k = 1;
    while (x >= k) m++, A[m] = a[i] * k, B[m] = k, id[m] = i, x -= k, k <<= 1;
    if (x) A[m] = a[i] * x, B[m] = x, id[m] = i;
}

inline void find(int x, int y) {
    if (!x) return;
    while (!pre[x][y]) y--;
    cnt[id[y]] += B[y];
    find(x - A[y], y - 1);
}

int main() {
    io >> n;
    For (i, 1, n) io >> a[i];
    For (i, 1, n) io >> b[i];
    io >> K;
    For (i, 1, n) solve(i);
    memset(f, 31, sizeof f);
    f[0] = 0;
    For (j, 1, m) rFor (i, K, A[j]) if (cmin(f[i], f[i - A[j]] + B[j])) pre[i][j] = 1;
    printf("%d\n", f[K]);
    find(K, m);
    For (i, 1, n) printf("%d ", cnt[i]);

    return 0;
} 
