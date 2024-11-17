#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
const int N = 2e5 + 5;
template<class C> inline bool cmin(C &x, const C &y) { return y<x? x=y, 1: 0; }
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

int T, n, m, ans, a[N], b[N << 1];
map<int, int > f[N];

int main() {
    io >> T;
    while (T--) {
        m = 0; ans = 2e9;
        io >> n;
        For (i, 1, n) io >> a[i], b[++m] = a[i];
        For (i, 2, n) b[++m] = a[i] + a[i - 1];
        sort(b + 1, b + m + 1); m = unique(b + 1, b + m + 1) - b - 1;
        For (i, 1, n) {
            int x = lower_bound(b + 1, b + m + 1, a[i]) - b;
            if (i == 1) f[i][x] = x;
            else {
                auto it = f[i - 1].upper_bound(x);
                if (it != f[i - 1].begin()) it--;
                for (; it != f[i - 1].end(); it++) {
                    int a = it->first, b = it->second; cmax(a, x);
                    if (b >= x) { cmax(f[i][a], x); break; }
                    cmax(f[i][a], b);
                }
            }
            if (i > 1) {
                x = lower_bound(b + 1, b + m + 1, a[i] + a[i - 1]) - b;
                if (i == 2) f[i][x] = x;
                else {
                    auto it = f[i - 2].upper_bound(x);
                    if (it != f[i - 2].begin()) it--;
                    for (; it != f[i - 2].end(); it++) {
                        int a = it->first, b = it->second; cmax(a, x);
                        if (b >= x) { cmax(f[i][a], x); break; }
                        cmax(f[i][a], b);
                    }
                }
                f[i - 2].clear();
            }
            vector<int > del;
            int lst = 0;
            for (auto &[x, y] : f[i]) if (!cmax(lst, y)) del.pb(x);
            for (auto &x : del) f[i].erase(x);
        }
        f[n - 1].clear();
        for (auto &[x, y] : f[n]) cmin(ans, b[x] - b[y]);
        f[n].clear();
        printf("%d\n", ans);
    }

    return 0;
}
