#include<bits/stdc++.h>
using namespace std;

#define pb push_back
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef long long ll;
const int N = 1e6 + 5;

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

int T, n, m, D, V, ans, tot, p[N];
vector<int > L[N], R[N];

int main() {
    io >> T;
    while (T--) {
        ans = tot = 0;
        io >> n >> m >> D >> V;
        For (i, 1, n) {
            int d, v, a;
            io >> d >> v >> a;
            if (v <= V && a <= 0) continue;
            int l, r;
            if (v > V) {
                l = d;
                if (a >= 0) r = D;
                else {
                    r = floor(0.5 * (V * V - v * v) / a);
                    if (V * V == v * v + 2 * a * r) r--;
                    r = min(D, d + r);
                }
            } else {
                l = ceil(0.5 * (V * V - v * v) / a);
                if (V * V == v * v + 2 * a * l) l++;
                if (d + l > D) continue;
                l = d + l; r = D;
            }
            if (l > r) continue;
            L[l].pb(r);
        }
        p[0] = -1; p[m + 1] = D + 1;
        For (i, 1, m) {
            io >> p[i];
            For (j, p[i - 1] + 1, p[i]) for (auto &r : L[j]) if (r >= p[i]) tot++, R[r].pb(i);
        }
        int lst = -1;
        For (i, 1, m) For (j, p[i], p[i + 1] - 1) for (auto &l : R[j]) if (l > lst) lst = i, ans++;
        printf("%d %d\n", tot, m - ans);
        For (i, 0, D) L[i].resize(0), R[i].resize(0);
    }

    return 0;
}
