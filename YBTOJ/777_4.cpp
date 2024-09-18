#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define rFor(i, r, l) for (int i = (r); i >= (l); --i)
#define For(i, l, r) for (int i = (l); i <= (r); ++i)
typedef double lf;
typedef pair<int, int > P;
const int N = 2e5 + 5;
const lf inf = 1e18;

int n;
P a[N], b[N], c[N];

inline lf dist(const P &a, const P &b) { return sqrt(1.l * (a.st - b.st) * (a.st - b.st) + 1.l * (a.nd - b.nd) * (a.nd - b.nd)); }
inline lf cir(const P &a, const P &b, const P &c) { return dist(a, b) + dist(a, c) + dist(b, c); }

lf solve(int l, int r) {
    if (l == r) return inf;
    int m = (l + r) >> 1;
    lf d1 = solve(l, m), d2 = solve(m + 1, r), d = min(d1, d2);
    int t = 0;
    For (i, l, r) if (abs(a[i].st - a[m].st) < d / 2) b[++t] = a[i];
    sort(b + 1, b + t + 1, [](P a, P b) { return a.nd < b.nd; });
    For (i, 1, t) {
        int p = 0;
        rFor (j, i - 1, 1) if (b[i].nd - b[j].nd < d / 2) c[++p] = b[j]; else break;
        For (j, i + 1, t) if (b[j].nd - b[i].nd < d / 2) c[++p] = b[j]; else break;
        For (j, 1, p) For (k, j + 1, p) d = min(d, cir(b[i], c[j], c[k]));
    }
    return d;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    For (i, 1, n) cin >> a[i].st >> a[i].nd;
    sort(a + 1, a + n + 1);
    printf("%.6lf\n", solve(1, n));

    return 0;
}
