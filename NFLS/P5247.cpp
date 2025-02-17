#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e6 + 5;

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

int T, n, mip[N], pri[N], psz, phi[N], a[128];
vector<vector<int > > f;

inline void init() {
    phi[1] = 1;
    For (i, 2, N - 1) {
        if (!mip[i]) pri[mip[i] = ++psz] = i, phi[i] = i - 1;
        For (j, 1, mip[i]) {
            int x = i * pri[j];
            if (x >= N) break;
            mip[x] = j, phi[x] = phi[i] * (pri[j] - (j != mip[i]));
        }
    }
}

inline void get(int n) {
    vector<int > g(phi[n] + 1); g[0] = a[0] = 1;
    int k = 0, x = n;
    while (x > 1) {
        int y = a[1 << k] = pri[mip[x]]; while (!(x % y)) x /= y;
        k++;
    }
    int S = 1 << k;
    For (i, 1, S - 1) a[i] = a[i & (i - 1)] * a[i & -i];
    For (i, 0, S - 1) {
        int x = n / a[i];
        if (__builtin_parity(i)) For (j, x, phi[n]) g[j] += g[j - x];
        else rFor (j, phi[n], x) g[j] -= g[j - x];
    }
    if (g[phi[n]] < 0) For (i, 0, phi[n]) g[i] = -g[i];
    f.pb(g);
}

inline void out(vector<int > f) {
    int n = f.size() - 1;
    putchar('(');
    rFor (i, n, 1) if (f[i]) {
        if (f[i] < 0) putchar('-'), f[i] = -f[i];
        else if (i < n) putchar('+');
        if (f[i] > 1) printf("%d", f[i]);
        putchar('x');
        if (i > 1) printf("^%d", i);
    }
    if (f[0] > 0) putchar('+');
    printf("%d)", f[0]);
}

inline bool cmp(const vector<int > &a, const vector<int > &b) {
    if (a.size() ^ b.size()) return a.size() < b.size();
    rFor (i, (int)a.size() - 1, 0) if (a[i] ^ b[i]) return a[i] < b[i];
    return 0;
}

int main() {
    freopen("factorization.in", "r", stdin);
    freopen("factorization.out", "w", stdout);
    init();
    io >> T;
    while (T--) {
        f.resize(0);
        io >> n;
        For (i, 1, n) if (!(n % i)) get(i);
        sort(f.begin(), f.end(), cmp);
        for (auto &g : f) out(g);
        puts("");
    }

    fclose(stdin); fclose(stdout);
    return 0;
}